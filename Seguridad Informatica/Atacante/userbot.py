from telethon.sync import TelegramClient, events
from telethon import functions, types
from telethon.tl.types import PeerChannel, PeerChat
import os

from argument_parser import parse_arguments, print_help

# Api hash y id registrada por nosotros[NO USAR PARA FINES MALOS]
api_id = ''
api_hash = ''
if os.path.isfile('./userApi.data'):
    with open('userApi.data', 'r') as data:
        temp = data.read().splitlines()
        api_id = temp[0]
        api_hash = temp[1]
else:
    print('completar api_id y api_hash en atacante.data')

client = TelegramClient('Denial', api_id, api_hash)
client.connect()

#Registral Cel para la sesion
phone_number = ""
session_key = ""
if os.path.isfile('./user.tel.data'):
    with open('user.tel.data', 'r') as data:
        temp = data.read().splitlines()
        phone_number = temp[0]
        session_key = temp[1]
else:
    with open('user.tel.data', 'a') as data:
        phone_number = input('ingresar numero (ejemplo +541155555555) ')
        data.write(phone_number + '\n')
        client.send_code_request(phone_number)
        session_key = input('se le envio una clave de sesion a su app de telegram, ingresela ')
        data.write(session_key)
        
print(phone_number, session_key)
myself = client.sign_in(phone_number, session_key)


# Intenta unirse al canal, OJO que si se puede unir Telethon cachea el entity
# internamente por lo que con solo el ID podemos mandar mensajes. Si ya estaba
# unido, tira una excepcion a lo cual le pedimos el chat id con CheckInvite,
# pero tenemos que pedir el entity (que es lo que realmente maneja telethon) con
# get_entity(PeerChat(..))
# Para obtener el Hash hay que fijarse el invite del channel y copiar lo que
# está despues de joinchat/...
chat_hash = 'D1gTRhyaH5duWeNoU2V_LA'
try:
    result = client(functions.messages.ImportChatInviteRequest(hash = chat_hash))
    chat_id = result.chats[0].id
except:
    result = client(functions.messages.CheckChatInviteRequest(hash = chat_hash))
    chat_id = result.chat.id

chat_entity = client.get_entity(PeerChat(chat_id))
client.send_message(chat_entity, 'Hello dudes!')

while (True):
    print_help()
    args = input("Enter command:\n")
    try:
        parse_arguments(args.split())
        client.send_message(chat_entity, "/attack " + args)
        break
    except SystemExit:
        print("Try again")

client.run_until_disconnected()

#!/bin/bash

kill_bot() {
  kill -TERM "$child" 2>/dev/null
}

trap kill_bot INT

pip3 install -r requirements.txt
python3 bot.py &
python3 userbot.py
echo "Closing tg-bot"
kill $(jobs -p)

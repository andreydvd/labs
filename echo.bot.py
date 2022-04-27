from pyowm.owm import OWM
from pyowm.utils.config import get_default_config
config_dict = get_default_config()
config_dict['language'] = 'ru'
import telebot

owm = OWM('f0d260681ccfc62a9854ee02a2dbfe44', config_dict)
mgr = owm.weather_manager()
bot = telebot.TeleBot("1696567607:AAGbvjkVmsl2VTYQ5KEtpR-lY2J5gNn0Ozk")

@bot.message_handler(commands=['start'])
def welcome(message):
    bot.send_message(message.chat.id, "Привет, {0.first_name}!\nЯ - {1.first_name}, созданный для поиска погоды.\nПодскажи, в каком городе ты хочешь узнать погоду?".format(message.from_user, bot.get_me()),)
@bot.message_handler(content_types=['text'])
def send_echo(message):
    observation = mgr.weather_at_place( message.text )
    w = observation.weather
    temp = w.temperature('celsius')["temp"]
    
    answer = "В городе " + message.text + " сейчас " + w.detailed_status + "\n"
    answer += "Температура в районе " + str(temp) + "\n\n"

    if temp < 0:
        answer += "Сейчас очень холодно, одевайся потеплее!"
    elif temp < 20:
        answer += "Сейчас прохладно, не забудь надеть тёплые вещи!"
    else:
        answer += "На улице тепло, одевайся как хочешь;)"
    bot.send_message(message.chat.id, answer)

bot.polling(none_stop=True)	

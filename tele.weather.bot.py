from pyowm.owm import OWM
from pyowm.utils.config import get_default_config
config_dict = get_default_config()
config_dict['language'] = 'ru'
owm = OWM('f0d260681ccfc62a9854ee02a2dbfe44', config_dict)
mgr = owm.weather_manager()
place = input('В каком городе/стране вас интересует погода? ')
observation = mgr.weather_at_place(place)
w = observation.weather
temp = w.temperature('celsius')["temp"]
print("В городе " + place + " сейчас " + w.detailed_status)
print("Температура в районе " + str(temp))
if temp < 0:
    print( "Сейчас очень холодно, одевайся потеплее!" )
elif temp < 20:
    print( "Сейчас прохладно, не забудь надеть тёплые вещи!" )
else:
    print( "На улице тепло, одевайся как хочешь;)" )
 

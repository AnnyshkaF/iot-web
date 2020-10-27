import os

CFG = {
    'port': int(os.getenv('WEB_SERVER_PORT', '20020')),
    'debug': False,
    'secret_key': '12345678',
    'users': {
        'admin': {'password': 'admin'}
    },
    'mqtt': {
        'host': os.getenv('MQTT_BROKER_HOST', 'localhost'),
        'port': int(os.getenv('MQTT_BROKER_PORT', '20021')),
        'login': os.getenv('MQTT_LOGIN', 'SimpleWeb'),
        'password': os.getenv('MQTT_PSWD', '')
    },
    'controls': [
        {
            'name': 'Switch off',
            'mqttTopic': 'system/time',
            'actions': [
                {'name': '6:00', 'mqttMessage': '6:00:00'},
                {'name': '12:00', 'mqttMessage': '12:00:00'},
                {'name': '18:00', 'mqttMessage': '18:00:00'},
                {'name': '24:00', 'mqttMessage': '24:00:00'}
            ]
        },
        {
            'name': 'Weather',
            'mqttTopic': 'system/weather',
            'actions': [
                {'name': 'Clear', 'mqttMessage': 'clear'},
                {'name': 'Raining', 'mqttMessage': 'raining'},
                {'name': 'Thundering', 'mqttMessage': 'thundering'}
            ]
        },
        {
            'name': 'All lights',
            'mqttTopic': '/room/allLights',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'turn on'},
                {'name': 'Turn off', 'mqttMessage': 'turn off'}
            ]
        },
        {
            'name': 'Lamp 1',
            'mqttTopic': '/room/light1',
            'actions': [
                {'name': 'Turn off', 'mqttMessage': '0'},
                {'name': '10%', 'mqttMessage': '10'},
                {'name': '20%', 'mqttMessage': '20'},
                {'name': '30%', 'mqttMessage': '30'},
                {'name': '40%', 'mqttMessage': '40'},
                {'name': '50%', 'mqttMessage': '50'},
                {'name': '60%', 'mqttMessage': '60'},
                {'name': '70%', 'mqttMessage': '70'},
                {'name': '80%', 'mqttMessage': '80'},
                {'name': '90%', 'mqttMessage': '90'},
                {'name': '100%', 'mqttMessage': '100'}
            ]
        },
        {
            'name': 'Lamp 2',
            'mqttTopic': '/room/light2',
            'actions': [
                {'name': 'Turn off', 'mqttMessage': '0'},
                {'name': '10%', 'mqttMessage': '10'},
                {'name': '20%', 'mqttMessage': '20'},
                {'name': '30%', 'mqttMessage': '30'},
                {'name': '40%', 'mqttMessage': '40'},
                {'name': '50%', 'mqttMessage': '50'},
                {'name': '60%', 'mqttMessage': '60'},
                {'name': '70%', 'mqttMessage': '70'},
                {'name': '80%', 'mqttMessage': '80'},
                {'name': '90%', 'mqttMessage': '90'},
                {'name': '100%', 'mqttMessage': '100'}
            ]
        },
        {
            'name': 'Relay Channel 1',
            'mqttTopic': '/room/stand/relay/channel1',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Relay Channel 2',
            'mqttTopic': '/room/stand/relay/channel2',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Relay Channel 3',
            'mqttTopic': '/room/stand/relay/channel3',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 1',
            'mqttTopic': '/room/ss1',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 2',
            'mqttTopic': '/room/ss2',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 3',
            'mqttTopic': '/room/ss3',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 4',
            'mqttTopic': '/room/ss4',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 5',
            'mqttTopic': '/room/ss5',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 6',
            'mqttTopic': '/room/ss6',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 7',
            'mqttTopic': '/room/ss7',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Smart Socket 8',
            'mqttTopic': '/room/ss8',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'on'},
                {'name': 'Turn off', 'mqttMessage': 'off'}
            ]
        },
        {
            'name': 'Intel Edison 1',
            'mqttTopic': '/room/small_lamp1',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'turn on'},
                {'name': 'Turn off', 'mqttMessage': 'turn off'}
            ]
        },
        {
            'name': 'Intel Edison 2',
            'mqttTopic': '/room/small_lamp2',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'turn on'},
                {'name': 'Turn off', 'mqttMessage': 'turn off'}
            ]
        },
        {
            'name': 'Intel Edison 3',
            'mqttTopic': '/room/small_lamp3',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'turn on'},
                {'name': 'Turn off', 'mqttMessage': 'turn off'}
            ]
        },
        {
            'name': 'Intel Edison 4',
            'mqttTopic': '/room/small_lamp4',
            'actions': [
                {'name': 'Turn on', 'mqttMessage': 'turn on'},
                {'name': 'Turn off', 'mqttMessage': 'turn off'}
            ]
        }
    ]
}

print(CFG)

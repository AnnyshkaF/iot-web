from flask import Flask
from flask import render_template
from flask import request
from flask import session
from flask import redirect
from flask import url_for
from random import uniform
import json
from config import CFG
from alc_config import ALC_CFG
import paho.mqtt.publish as publish

app = Flask(__name__, static_folder='static')

stateOfSomething1 = 0   #ANNA: initial state of the buttons
stateOfSomething2 = 0

@app.route('/')
def mainPage():
    if 'login' not in session:
        return redirect('/auth')
    
    return render_template('main.html')
    #return '123' #{'n':10,'a':[1,2,3]} #json
    #return """ <html> 
    # <head>
    # Test {}
    #<a href = "/test"> to test</a>
    # </head>
    # </html>
    # """.format{val}

@app.route('/controls')
def controlsPage():
    if 'login' not in session:
        return redirect('/auth')
    
    d = {'controls': CFG['controls']}
    return render_template('controls.html', **d)

@app.route('/auth', methods = ['GET', 'POST'])
def authPage():
    if 'login' in session:
        return redirect('/')
    
    login = request.values.get('login')
    password = request.values.get('password')
    
    d = {}
    if login != None and password != None:
        if login in CFG['users']:
            if CFG['users'][login]['password'] == password:
                session['login'] = login
                print('User {} logged in'.format(login))
                return redirect('/')
            else:
                d['errorMessage'] = 'Incorrect login or/and password 1';
        else:
            d['errorMessage'] = 'Incorrect login or/and password 2';
    return render_template('auth.html', **d)

@app.route('/logout')
def logoutPage():
    if 'login' in session:
        print('User {} logged out'.format(session['login']))
        session.pop('login')
        
    return redirect('/auth')

#8,9
@app.route('/findWorker', methods = ['GET','POST'])
def findWorker():
    name = request.values.get('name')
    surname = request.values.get('surname')
    id = request.values.get('id')

    # POST is proccessed at first in 
    # asumption that GET may be still in request
    d = {}; k = [];
    users = ALC_CFG['workers']
    if id != None:
        for u in users:
            print(u['id'] == str(id))
            if (u['id'] == str(id)):
                k.append(u);
        d = {'people': k}
        return render_template('find_worker.html', **d)  

    if name != None or surname != None:
        for u in users:
            if (u['surname'] == surname or u['name'] == name):
                k.append(u);
        d = {'people': k}
        return render_template('find_worker.html', **d)        

    #print(d)
    d = {'people': k}
    return render_template('find_worker.html', **d)

@app.route('/api/addWorker', methods = ['GET','POST'])
def addWorker():
    name = request.values.get('name')
    surname = request.values.get('surname')
    age = request.values.get('age')

    # POST is proccessed at first in 
    # asumption that GET may be still in request
    d = {}; k = [];
    users = ALC_CFG['workers']
    if id != None:
        for u in users:
            print(u['id'] == str(id))
            if (u['id'] == str(id)):
                k.append(u);
        d = {'people': k}
        return render_template('find_worker.html', **d)  

    if name != None or surname != None:
        for u in users:
            if (u['surname'] == surname or u['name'] == name):
                k.append(u);
        d = {'people': k}
        return render_template('find_worker.html', **d)        

    #print(d)
    d = {'people': k}
    return render_template('find_worker.html', **d)

@app.route('/alc_info', methods = ['GET', 'POST'])
def aclPage(): 
    weight = request.values.get('weight')
    print(weight)
    volume = request.values.get('volume')

    #names = ALC_CFG['name'];
    names = ['pivo4', 'pivo6', 'vodka']
    for n in names:
        hour = 2#(names[weight][volume]['hour']);
        min = 30 #(names[weight][volume]['min']);

    if(weight == None or volume == None):
        d = {'weight': 70, 'volume' : 100};
    else:
        d = {'weight': weight, 'volume' : volume, 'hour' : hour, 'min': min}

    return render_template('alc_info.html', **d)

@app.route('/settings')
def settingsPage():
    if 'login' not in session:
        return redirect('/auth')
    
    return render_template('settings.html')

@app.route('/about')
def aboutPage():
    if 'login' not in session:
        return redirect('/auth')
    
    return render_template('about.html')
#10
#Data is generated here
@app.route('/api/getData')
def apiGetData():
    if 'login' not in session:
        return {}
    
    global stateOfSomething1
    global stateOfSomething2
    
    alcMin = 0.0
    alcMax = 100.0
    alc = uniform(alcMin, alcMax)
    alcLoad = (alc - alcMin) / (alcMax - alcMin) * 100.0
    alcAlert = alc > 95

    tempMin = -20.0
    tempMax = 35.0
    temp = uniform(tempMin, tempMax);
    tempLoad = (temp - tempMin) / (tempMax - tempMin) * 100.0;
    tempAlert = temp > 27.0
    
    lightMin = 0.0
    lightMax = 400.0
    light = uniform(lightMin, lightMax)
    lightLoad = (light - lightMin) / (lightMax - lightMin) * 100.0
    lightAlert = light > 300.0
    
    humidityMin = 0.0
    humidityMax = 100.0
    humidity = uniform(humidityMin, humidityMax)
    humidityLoad = (humidity - humidityMin) / (humidityMax - humidityMin) * 100.0
    humidityAlert = humidity > 95


    
    return {
        'alcohol': {
            'value': '{:.1f}'.format(alc),
            'load': alcLoad,
            'alert': alcAlert,
            'unit': '\u2103'
        },
        'temperature': {
            'value': '{:.1f}'.format(temp),
            'load': tempLoad,
            'alert': tempAlert,
            'unit': '\u2103'
        },
        'light': {
            'value': '{:.1f}'.format(light),
            'load': lightLoad,
            'alert': lightAlert,
            'unit': 'lux'
        },
        'humidity': {
            'value': '{:.1f}'.format(humidity),
            'load': humidityLoad,
            'alert': humidityAlert,
            'unit': 'hum'
        },
        'stateOfSomething1': {
            'state': stateOfSomething1,
            'name': 'button1'
        },
        'stateOfSomething2': {
            'state': stateOfSomething2,
            'name': 'button2'
        }
    }

@app.route('/api/loadData')
def loadData():
    if 'login' not in session:
        return {}
    
    global stateOfSomething1
    global stateOfSomething2
    
    b = []
    with open('save.json') as json_file:
        data = json.load(json_file)
        for d in data['buttons']:
            b.append(int(d['state']))
    json_file.close()       
    stateOfSomething1 = b[0]        
    stateOfSomething2 = b[1]

    return {
        'button1': {
            'state': stateOfSomething1,
            'name': 'button1'
        },
        'button2': {
            'state': stateOfSomething2,
            'name': 'button2'
        }
    }

@app.route('/api/saveData')
def saveData():
    if 'login' not in session:
        return {}
    
    global stateOfSomething1
    global stateOfSomething2
    
    data = {
    "buttons": [
        {"name": "button1", "state": stateOfSomething1},
        {"name": "button2", "state": stateOfSomething2}
        ]
    }
    with open('save.json', 'w') as outfile:
        json.dump(data, outfile)
        outfile.close()  
    return data

@app.route('/api/saveWorkers', methods = ['POST'])
def saveWorker():
    if 'login' not in session:
        return {}
    
    name = request.args.get('name')
    surname = request.args.get('surname')
    age = request.args.get('age')
    b = []

    #read workers base
    json_file = open('worker.json','r+')
    data = json.load(json_file)
    new_id = len(data['workers'])
    new_worker = {'id' : new_id, 'name': name, 'surname' : surname, 'age' : age}
    for d in data['workers']:
        b.append(d)
        if(d == new_worker):
            json_file.close()  
            return {'message' : 'Worker already exists'}
                
    b.append(new_worker)
    b = {"workers" : [b]}
    #write workers base to json_file
    json.dump(b, json_file)
    json_file.close()  
    return {'message' : 'Worker is added'}


    return {
        'button1': {
            'state': stateOfSomething1,
            'name': 'button1'
        },
        'button2': {
            'state': stateOfSomething2,
            'name': 'button2'
        }
    }

@app.route('/api/changeStateOfSomething1', methods = ['GET'])
def apiChangeStateOfSomething1():
    if 'login' not in session:
        return {}
    
    global stateOfSomething1
    
    newState = request.args.get('newState')
    print(newState)
    if newState in [0, 1, '0', '1']:
        stateOfSomething1 = newState
        return {'result': 1}
    else:
        return {'result': 0}

@app.route('/api/changeStateOfSomething2', methods = ['GET'])
def apiChangeStateOfSomething2():
    if 'login' not in session:
        return {}
    
    global stateOfSomething2
    
    newState = request.args.get('newState')
    print(newState)
    if newState in [0, 1, '0', '1']:
        stateOfSomething2 = newState
        return {'result': 1}
    else:
        return {'result': 0}

@app.route('/api/activateAction', methods = ['GET'])
def apiActivateAction():
    if 'login' not in session:
        return {}
    
    globalActionId = request.args.get('globalActionId', type=int)
    
    if globalActionId in CFG['mapOfGlobalActions']:
        param = CFG['mapOfGlobalActions'][globalActionId]
        
        mqttTopic = CFG['controls'][param['iControl']]['mqttTopic']
        mqttMessage = CFG['controls'][param['iControl']]['actions'][param['iAction']]['mqttMessage']
        
        try:
            publish.single( mqttTopic,
                            mqttMessage,
                            hostname=CFG['mqtt']['host'],
                            port=CFG['mqtt']['port'],
                            auth={'username': CFG['mqtt']['login'], 'password': CFG['mqtt']['password']})
        except Exception as e:
            print('ERROR: {}'.format(e))
            return {'result': 0}
        
        return {'result': 1}
    
    return {'result': 0}

@app.errorhandler(404)
def notFoundPage(error):
    if 'login' in session:
        return render_template('error_with_menu.html'), 404
    else:
        return render_template('error.html'), 404

if __name__ == '__main__':
    
    globalActionId = 0
    CFG['mapOfGlobalActions'] = {}
    for iCtrl in range(len(CFG['controls'])):
        for iAction in range(len(CFG['controls'][iCtrl]['actions'])):
            CFG['controls'][iCtrl]['actions'][iAction]['globalActionId'] = globalActionId
            CFG['mapOfGlobalActions'][globalActionId] = {'iControl': iCtrl, 'iAction': iAction}
            globalActionId += 1
    
    app.secret_key = CFG['secret_key']
    
    app.run(host='0.0.0.0', port = CFG['port'], debug = CFG['debug'])


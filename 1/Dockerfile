FROM python:3.7

WORKDIR /SimpleIoTControlPanel

COPY www requirements.txt ./

RUN pip3 install -r requirements.txt

ENV WEB_SEVER_PORT=1024 \
	MQTT_BROKER_HOST=localhost \
	MQTT_BROKER_PORT=1024 \
	MQTT_LOGIN=SimpleWeb \
	MQTT_PSWD=None

CMD [ "python3", "-u", "app.py" ]

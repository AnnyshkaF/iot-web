var temp = document.getElementById("temperature_indicator");
var light = document.getElementById("light_indicator");
var humidity = document.getElementById("humidity_indicator");
var button1 = document.getElementById("button_1");
var button2 = document.getElementById("button_2");
var lineContent = document.getElementById('bar-content');
var cylinderContent = document.getElementById('cylinder-content');
svgHours   = document.querySelector("#hours");
svgMinutes = document.querySelector("#minutes");

//text input
var tbutton1 = document.getElementById("tbutton_1");
var tbutton2 = document.getElementById("tbutton_2");

var lastStateOfButton1 = 0, lastStateOfButton2 = 0;

button1.onclick = function(){
	var newState = lastStateOfButton1 == 1 ? 0 : 1;
	fetch("/api/changeStateOfSomething1?newState=" + newState)
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result != 1)
				throw new Exception("Unsuccessful result");
			
			lastStateOfButton1 = newState;
			updateButtonIndicator(button1, {state: newState, name: "---"});
			saveData()
		})
		.catch(function(err){
			console.log(err);
		});
}

//Пункт 8
//GET
/*button2.onclick = function(){
	var newState = lastStateOfButton2 == 1 ? 0 : 1;
	fetch("/api/changeStateOfSomething2?newState=" + (lastStateOfButton2 == 1 ? 0 : 1))
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result != 1)
				throw new Exception("Unsuccessful result");
			
			lastStateOfButton2 = newState;
			updateButtonIndicator(button2, {state: newState, name: "..."});
			saveData()
		})
		.catch(function(err){
			console.log(err);
		});
}*/

//POST request
button2.onclick = function(){
	console.log('in func');
	var newState = lastStateOfButton2 == 1 ? 0 : 1;

	fetch("/api/changeStateOfSomething2",{
	method: "POST",
	body: JSON.stringify({ "newState": newState}),
	headers: new Headers({
        "content-type": "application/json"
      })
	}).then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result != 1)
				throw new Exception("Unsuccessful result");
			
			lastStateOfButton2 = newState;
			updateButtonIndicator(button2, {state: newState, name: "..."});
			saveData()
		})
		.catch(function(err){
			console.log(err);
		});
}

tbutton1.onclick = function(){
	var newState = document.getElementById("button-input1").value;
	fetch("/api/changeStateOfSomething1?newState=" + newState)
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result != 1)
				throw new Exception("Unsuccessful result");
			
			lastStateOfButton1 = newState;
			updateButtonIndicator(button1, {state: newState, name: "---"});
			saveData()
		})
		.catch(function(err){
			console.log(err);
		});
		document.getElementById("button-input1").value=""
}

tbutton2.onclick = function(){
	var newState = document.getElementById("button-input2").value;
	fetch("/api/changeStateOfSomething2?newState=" + newState)
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result != 1)
				throw new Exception("Unsuccessful result");
			
			lastStateOfButton2 = newState;
			updateButtonIndicator(button2, {state: newState, name: "..."});
			saveData()
		})
		.catch(function(err){
			console.log(err);
		});
		document.getElementById("button-input2").value=""
}

function initWatch(){
	let  dt = new Date(),
		hours = dt.getHours(),
		minutes = dt.getMinutes(),
		seconds = dt.getSeconds(),
		degSeconds = 180 + 360/60 * seconds,
		degMinutes = 180 + 360/60 * minutes,
		degHours =   180 + 360/12 * ( hours % 12 ) + degMinutes/60;
		
	
		svgHours.setAttribute('transform',`translate(18,18) rotate(${degHours} 0 0)`);
		svgMinutes.setAttribute('transform',`translate(18,18) rotate(${degMinutes} 0 0)`);
		console.clear();
		console.log(dt.toLocaleTimeString());
		console.log(hours);
		console.log(seconds);
}

//Update the cylinder progress bar
function updateProgressCylinder (value){
  var rect = cylinderContent.querySelector("#rect");
  var topEllipse = cylinderContent.querySelector("#el_top");

  //0% =  {y:90, height:0} / 100% = {y:20, height:80}
  rect.setAttribute('height', (80-(value*.8)));
  // 20 = 100% -- 100 = 0%
  rect.setAttribute('y', (value*.8)+20);
  topEllipse.setAttribute('cy',((-value*-.8)+20));

  var percentageVal = cylinderContent.querySelector("#percentage_cyl");
  percentageVal.textContent = (100-value) + "%";
}

//Update the line progress bar
function updateProgressLine(value){  
	var percentageBar = lineContent.querySelector("#line");
	percentageBar.setAttribute('stroke-dashoffset', value);

	var percentageVal = lineContent.querySelector("#percentage_bar");
	percentageVal.textContent = (100-value) + "%";
}

//Update the content fill value
var updateProgressValue = function(data){
	updateProgressLine(Math.round(data.value));
	updateProgressCylinder(Math.round(data.value));
}

function updateLoadIndicator(element, data){
	var value = element.querySelector("#value");
	if(value.textContent != data.value)
		value.textContent = data.value;
	
	var unit = element.querySelector("#unit");
	if(unit.textContent != data.unit)
		unit.textContent = data.unit;
	
	var load = element.querySelector("#load");
	if(data.load == 100)
		data.load = 99.999;
	var angle = 360 * data.load / 100 - 270;
	var angleRad = angle / 360 * 2 * Math.PI;
	var x = Math.cos(angleRad), y = Math.sin(angleRad);
	x *= 50;
	y *= 50;
	var f = data.load <= 50 ? 0 : 1;
	load.setAttribute("d", "M 0,0 l 0,50 A 50,50 -90 " + f + ",1 " + x + "," + y + " z");
	load.classList.toggle("indicator-normal-state", data.alert != 1);
	load.classList.toggle("indicator-alert-state", data.alert == 1);
}

function updateButtonIndicator(element, data){
	var state = element.querySelector("#state");
	var stateName = data.state == 1 ? "ON" : "OFF";
	if(state.textContent != stateName)
		state.textContent = stateName;
	
	var name = element.querySelector("#name");
	if(name.textContent != data.name)
		name.textContent = data.name;
	
	var backlight = element.querySelector("#backlight");
	backlight.classList.toggle("indicator-on-state", data.state == 1);
	backlight.classList.toggle("indicator-off-state", data.state != 1);
}

function loop(){
	fetch("/api/getData")
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			updateProgressValue(d.alcohol);
			if(lastStateOfButton1 == 1){
				updateLoadIndicator(temp, d.temperature);
			}else{
				updateLoadIndicator(temp, {value: "-", unit: "-", alert: 0, load: 0});
			}
			if(lastStateOfButton2 == 1){
				updateLoadIndicator(light, d.pulse);
			}else{
				updateLoadIndicator(light, {value: "-", unit: "-", alert: 0, load: 0});
			}
			updateButtonIndicator(button1, d.stateOfSomething1);
			updateButtonIndicator(button2, d.stateOfSomething2);
			
			lastStateOfButton1 = d.stateOfSomething1.state;
			lastStateOfButton2 = d.stateOfSomething2.state;
			
			setTimeout(loop, 1000);
		})
		.catch(function(err){
			console.log(err);
			setTimeout(loop, 1000);
		});
}

function animation(){
	if(this.nIteration === undefined)
		this.nIteration = 200;
	
	if(this.nIteration == 0){
		loop();
		return;
	}
	
	if(this.nIteration > 100){
		var val = 100 - (this.nIteration - 100);
		updateLoadIndicator(temp, {value: "-", unit: "-", alert: 0, load: val});
		updateLoadIndicator(light, {value: "-", unit: "-", alert: 0, load: val});
	}else{
		var val = this.nIteration;
		updateLoadIndicator(temp, {value: "-", unit: "-", alert: 0, load: val});
		updateLoadIndicator(light, {value: "-", unit: "-", alert: 0, load: val});
	}
	updateProgressValue({value: val, unit: "-", alert: 0, load: val});
	
	this.nIteration = this.nIteration - 2;
	setTimeout(animation, 10);
}

loadData()
animation();

function loadData(){
	fetch("/api/loadData")
		.then(function(d){
			return d.json();
		}).then(function(d){
			lastStateOfButton1 = parseInt(d['button1']['state']);
			lastStateOfButton2 = parseInt(d['button2']['state']);
			console.log('but1 = ' + lastStateOfButton1);
			console.log('but2 = ' + lastStateOfButton2);
		})
		.catch(function(err){
			console.log(err);
		});
}

function saveData(){
	fetch("/api/saveData")
		.then(function(d){
			return d.json();
		})
		.catch(function(err){
			console.log(err);
		});
}
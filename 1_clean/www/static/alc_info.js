var val = document.getElementById('ranger');
var button1 = document.getElementById("button_1");
var button2 = document.getElementById("alc_button");

svgHours   = document.querySelector("#beer4_hours"),
svgMinutes = document.querySelector("#beer4_minutes"),
	   
val.onclick = function(){
	document.getElementById('rangeValue').innerHTML = document.getElementById('ranger').value;
}

//function setWatch(){
button2.onclick = function(){
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

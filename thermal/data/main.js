function clamp( x, min, max ) {

    if(x<min){ return min; }
    if(x>max){ return max; }

    return x;
}

function colorTemperatureToRGB(temp){
	var maxTemp = 50;
	var minTemp = 0;
	var blue = 255 / (maxTemp - minTemp) * (maxTemp - temp);
	var red = 0;
	var green = 255 / (maxTemp - minTemp) * (temp - minTemp);
    return {
        r : clamp(red,   0, 255),
        g : clamp(green, 0, 255),
        b : clamp(blue,  0, 255)
    }
}

function loop(){
	fetch("/api/getData")
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			for (let i = 0; i < 8; i++)
			{
				for (let j = 0; j < 8; j++) 
				{
					idname = "a" + i.toString() + j.toString();
					valuename = "d." + idname;
					value = eval(valuename); 
					let res = "" + valuename + ":" + value.toString();
					//console.log(res);
					var p = document.getElementById(idname);
					let rgb = colorTemperatureToRGB(value);
					//console.log(rgb);
					p.style='fill:rgb(' + rgb.r.toString() + ','+ rgb.g.toString() + ',' + rgb.b.toString() + ')';
				}
			}	
			setTimeout(loop, 500);
		})
		.catch(function(err){
			console.log(err);
			setTimeout(loop, 1000);
		});
}

loop();

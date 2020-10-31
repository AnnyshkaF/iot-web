function activateAction(globalActionId){
	var e = document.getElementById("a" + globalActionId);
	var children = e.parentNode.childNodes;
	var delay = 25;
	
	fetch("/api/activateAction?globalActionId=" + globalActionId)
		.then(function(d){
			return d.json();
		})
		.then(function(d){
			if(d.result == 0){
				e.classList.toggle("failure", 1);
				for(var i = 0; i < children.length; ++i)
					children[i].disabled = 1;
				
				setTimeout(function(){
					e.classList.toggle("failure", 0);
					for(var i = 0; i < children.length; ++i)
						children[i].disabled = 0;
				}, delay * 10);
			}else{
				e.classList.toggle("success", 1);
				for(var i = 0; i < children.length; ++i)
					children[i].disabled = 1;
				
				setTimeout(function(){
					e.classList.toggle("success", 0);
					for(var i = 0; i < children.length; ++i)
						children[i].disabled = 0;
				}, delay);
			}
				
		})
		.catch(function(err){
			e.classList.toggle("failure", 1);
			setTimeout(function(){
				e.classList.toggle("failure", 0);
			}, delay);
			console.log(err);
		});
}

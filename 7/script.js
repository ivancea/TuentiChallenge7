var cells = document.getElementsByTagName("td");
var rows = Math.sqrt(cells.length);
var mat = {};

for(var i=0; i<rows; i++){
	for(var j=0; j<rows; j++){
		mat[i+'-'+j] = {
			letter: cells[i + j*rows].innerHTML,
			cell: cells[i + j*rows]
		};
	}
}

var wordsElement = document.getElementById("words");
var wordElementChildren = wordsElement.getElementsByTagName("div");
var words = [];

for(var i=0; i<wordElementChildren.length; i++){
	if(wordElementChildren[i].id != "time-left" && wordElementChildren[i].id != ""){
		words.push(wordElementChildren[i].innerHTML);
	}
}

function m(t) {
	let n, e, o, s = 0;
	const c = t + "-saltbae";
	if (!c.length) return s;
	for (n = 0, o = c.length; n < o; n++) e = c.charCodeAt(n), s = (s << 5) - s + e, s |= 0;
	return Math.abs(s);
};

function next(matrix, rowCount, pos, direction){
	switch(direction){
		case 0: pos.x++; break;
		case 1: pos.x++;pos.y++; break;
		case 2: pos.y++; break;
		case 3: pos.y++;pos.x--; break;
		case 4: pos.x--; break;
		case 5: pos.x--;pos.y--; break;
		case 6: pos.y--; break;
		case 7: pos.x++;pos.y--; break;
	}
	return pos.x >= 0 && pos.y >= 0 && pos.x < rowCount && pos.y < rowCount;
}

// Solve
for(var i=0; i<words.length; i++){
	var wordDone = false;
	for(var x=0; x<rows && wordDone === false; x++){
		for(var y=0; y<rows && wordDone === false; y++){
			
			for(var dir=0; dir<8 && wordDone === false; dir++){
				var c = 0;
				var pos = {x: x, y: y};
				do{
					if(mat[pos.x+"-"+pos.y].letter != words[i][c]){
						break;
					}else if(c+1 == words[i].length){
						wordDone = {x1: x, y1: y,
									x2: pos.x, y2: pos.y};
						break;
					}
					c++;
				}while(next(mat, rows, pos, dir));
			}
			
		}
	}
	if(wordDone === false){
		alert("Couldn't find word: " + words[i]);
	}else{
		var t = wordDone;
		var k = t.x1+"-"+t.y1+"-"+t.x2+"-"+t.y2;
		w.send(btoa(k+"-"+m(k)));
	}
}
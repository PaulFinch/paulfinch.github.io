function start() {
	setInterval(worker, 1000);
}

function worker() {
	var today = new Date();
	today.getTime();

	var date = today.getDate() * 10000 + (today.getMonth() + 1) * 100 + (today.getFullYear() % 100);
	var time = today.getHours() * 10000 + today.getMinutes() * 100 + today.getSeconds();

	show_binaries(get_binaries(date), 'd');
	show_binaries(get_binaries(time), 'h');
}

function get_binary(figure) {
	var binary = [0, 0, 0, 0];

	for (k = 3; k >= 0; k--) {
		var pw = Math.pow(2, k);
		var val = Math.floor(figure / pw);
		figure = figure - (val * pw);
		binary[k] = val;
	}

	return binary;
}

function get_binaries(number) {
	var binaries = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]];

	for (i = 5; i >= 0; i--) {
		var power = Math.pow(10, i);
		var value = Math.floor(number / power);
		number = number - (value * power);
		binaries[i] = get_binary(value);
	}

	return binaries;
}

function show_binaries(binaries, tr) {
	for (i = 5; i >= 0; i--) {
		for (j = 3; j >= 0; j--) {
			var index = (i * 4) + j;
			if (binaries[i][j] == 0)
				document.getElementById(tr + 'radio' + index).checked = false;
			else
				document.getElementById(tr + 'radio' + index).checked = true;
		}
	}
}

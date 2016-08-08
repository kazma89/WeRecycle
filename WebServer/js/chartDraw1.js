//-------------------------------------------new code----------------------------------------------------------------//
google.charts.load("current", {'packages':['gauge']}); 

function drawGauge1(dato1){
    console.log(dato1);
    console.log("------------------");
    console.log(parseInt(dato1));
  var data1 = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['Plastico', parseInt(dato1) ],
        ]);
  
  var options1 = {
    width: 240, height: 240,
    redFrom: 90, redTo: 100,
    yellowFrom: 75, yellowTo: 90,
    minorTicks: 5
  };

  var chart1 = new google.visualization.Gauge(document.getElementById('chart_div1'));
  chart1.draw(data1, options1);
    //En caso de que alcance lo amarillo lance una alerta o un pop-up
  setInterval(function() {
      getData();
  }, 5000)
}

function drawGauge2(dato2){
    console.log(dato2);
    console.log("------------------");
    console.log(parseInt(dato2));
  var data2 = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['Aluminio', parseInt(dato2) ],
        ]);
  
  var options2 = {
    width: 240, height: 240,
    redFrom: 90, redTo: 100,
    yellowFrom: 75, yellowTo: 90,
    minorTicks: 5
  };

  var chart2 = new google.visualization.Gauge(document.getElementById('chart_div2'));
  chart2.draw(data2, options2);
    //En caso de que alcance lo amarillo lance una alerta o un pop-up
  setInterval(function() {
      getData();
  }, 5000)
}

function drawGauge3(dato3){
    console.log(dato3);
    console.log("------------------");
    console.log(parseInt(dato3));
  var data3 = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['NC', parseInt(dato3) ],
        ]);
  
  var options3 = {
    width: 240, height: 240,
    redFrom: 90, redTo: 100,
    yellowFrom: 75, yellowTo: 90,
    minorTicks: 5
  };

  var chart3 = new google.visualization.Gauge(document.getElementById('chart_div3'));
  chart3.draw(data3, options3);
    //En caso de que alcance lo amarillo lance una alerta o un pop-up
  setInterval(function() {
      getData();
  }, 5000)
}

//Función para obtener la información de la base de datos
function getData(){  
  var setHeader = function (req) {
    req.setRequestHeader('content-type', 'application/json'); 
    req.setRequestHeader('accept', 'application/json'); 
  }; 
  $.ajax({
    type: "GET",
    url: "http://hwthoncr16.herokuapp.com/x/last",
    beforeSend: setHeader,
    success: function(res){
        console.log(res);
        drawGauge1(res.Tacometro1);//Invoca la función que dibuja el gráfico 1
        drawGauge2(res.Tacometro2);//Invoca la función que dibuja el gráfico 2
        drawGauge3(res.Tacometro3);//Invoca la función que dibuja el gráfico 3
    }
  });
};
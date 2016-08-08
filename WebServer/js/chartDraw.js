//-------------------------------------------new code---------------------------------------------------------------- 
google.charts.load("current", {'packages':['gauge']});

function drawGauge(dato1, dato2, dato3){
    console.log(dato1);
    console.log(dato2);
    console.log(dato3);
    console.log("------------------");
    console.log(parseInt(dato1));
    console.log(parseInt(dato2));
    console.log(parseInt(dato3));
  var data = google.visualization.arrayToDataTable([
          ['Label', 'Value'],
          ['Plastico', parseInt(dato1) ],
          ['Aluminio', parseInt(dato2)],
          ['NC', parseInt(dato3) ]
        ]);
  

  var options = {
    width: 240, height: 240,
    redFrom: 90, redTo: 100,
    yellowFrom: 75, yellowTo: 90,
    minorTicks: 5
  };

  var chart = new google.visualization.Gauge(document.getElementById('chart_div'));
  chart.draw(data, options);
    
  setInterval(function() {
      getData();
  }, 3000)
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
      drawGauge(res.Tacometro1,res.Tacometro2,res.Tacometro3);//Invoca la función que dibuja el gráfico
    }
  });
};


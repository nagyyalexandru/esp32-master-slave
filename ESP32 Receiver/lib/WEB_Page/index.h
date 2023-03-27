#define WebPage_h
#ifdef WebPage_h
#include "Arduino.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32</title>
  <meta name="viewport" content="width=device-width">
  <style>
    body {
  margin: 40px;
}

.wrapper {
  display: grid;
  grid-template-columns: 170px 170px 170px;
  grid-gap: 10px;
  background-color: #fff;
  color: #9f9f9f;
}

.box {
  background-color: #444;
  color: #fff;
  border-radius: 5px;
  padding: 20px;
  font-size: 150%;
}
  </style>
</head>

<body>
    <div class="top-nav">
        <h2>ESP32 Web Server</h2>
    </div>

    <div class="wrapper">
  <div class="box a">
  <p>DHT22 Temperatura</p>
  <p><span class="reading"><span id="t1"></span> &deg;C</span></p>
  </div>
  <div class="box b">
  <p>DHT22 Umiditate</p>
  <p><span class="reading"><span id="h1"></span> &percnt;</span></p>
  </div>
  <div class="box c">
  <p>Pot 1 Viteza</p>
  <p><span class="reading"><span id="s1"></span> km/h</span></p>
  </div>
  <div class="box d">
  <p>Pot 2 combustibil</p>
  <p><span class="reading"><span id="f1"></span> / 4</span></p>
  </div>
  <div class="box e">
  <p>Buton 1 Faza scurta</p>
  <p><span class="reading"><span id="lowb1"></span></span></p>
  </div>
  <div class="box f">
  <p>Buton 2 Faza lunga</p>
  <p><span class="reading"><span id="highb1"></span></span></p>
  </div>
  <div class="box g">
  <p>Senzor ultrasonic</p>
  <p><span class="reading"><span id="dis1"></span> metri</span></p>
  </div>
</div>

  <script>
    if (!!window.EventSource) {
      var source = new EventSource('/events');

      source.addEventListener('open', function (e) {
        console.log("Events Connected");
      }, false);
      source.addEventListener('error', function (e) {
        if (e.target.readyState != EventSource.OPEN) {
          console.log("Events Disconnected");
        }
      }, false);

      source.addEventListener('message', function (e) {
        console.log("message", e.data);
      }, false);

      source.addEventListener('new_message', function (e) {
        console.log("new_message", e.data);
        var obj = JSON.parse(e.data);
        document.getElementById("t" + obj.id).innerHTML = obj.temperature.toFixed(1);
        document.getElementById("h" + obj.id).innerHTML = obj.humidity.toFixed(1);
        document.getElementById("s" + obj.id).innerHTML = obj.speed.toFixed();
        document.getElementById("f" + obj.id).innerHTML = obj.fuel.toFixed();
        document.getElementById("lowb" + obj.id).innerHTML = obj.lowbeam.toFixed();
        document.getElementById("highb" + obj.id).innerHTML = obj.highbeam.toFixed();
        document.getElementById("dis" + obj.id).innerHTML = obj.distance.toFixed();
      }, false);
    }
  </script>
</body>
</html>)rawliteral";
#endif
// #define WebPage_h
// #ifdef WebPage_h
// #include "Arduino.h"
// #include "CommonDataE.h"

// const char index_html[] PROGMEM = R"rawliteral(
// <!DOCTYPE HTML><html>
// <head>
//   <title>ESP32</title>
//   <meta name="viewport" content="width=device-width">
//   <style>
//     html {
//       font-family: Arial;
//       display: inline-block;
//       text-align: center;
//     }

//     p {
//       font-size: 1.2rem;
//     }

//     body {
//       margin: 0;
//     }

//     .topnav {
//       overflow: hidden;
//       background-color: #ee721f;
//       color: white;
//       font-size: 1.7rem;
//     }

//     .content {
//       padding: 20px;
//     }

//     .card {
//       background-color: rgb(44, 153, 255);
//       color: #000000;
//     }

//     .cards {
//       max-width: 700px;
//       margin: 0 auto;
//       display: grid;
//       grid-gap: 2rem;
//       grid-template-columns: repeat(auto-fit, minmax(500px, 1fr));
//     }

//     .reading {
//       font-size: 2.8rem;
//     }

//     .packet {
//       color: #ffffff;
//     }
//   </style>
// </head>

// <body>
//   <div class="topnav">
//     <h3>ESP32 Web Serveer</h3>
//   </div>
//   <div class="content">
//     <div class="cards">
//       <div class="card">
//         <h4>TEMPERATURE</h4>
//         <p><span class="reading"><span id="t1"></span> &deg;C</span></p>
//         <p class="packet">Reading : <span id="rt1"></span></p>
//       </div>
//       <div class="card">
//         <h4>HUMIDITY</h4>
//         <p><span class="reading"><span id="h1"></span> &percnt;</span></p>
//         <p class="packet">Reading : <span id="rh1"></span></p>
//       </div>
//       <div class="card">
//         <h4>SPEED</h4>
//         <p><span class="reading"><span id="s1"></span> km/h</span></p>
//       </div>
//       <div class="card">
//         <h4>FUEL LEVEL</h4>
//         <p><span class="reading"><span id="f1"></span> / 4</span></p>
//       </div>
//       <div class="card">
//         <h4>DANGER IN</h4>
//         <p><span class="reading"><span id="dis1"></span> meters</span></p>
//       </div>
//     </div>
//   </div>
//   <script>
//     if (!!window.EventSource) {
//       var source = new EventSource('/events');

//       source.addEventListener('open', function (e) {
//         console.log("Events Connected");
//       }, false);
//       source.addEventListener('error', function (e) {
//         if (e.target.readyState != EventSource.OPEN) {
//           console.log("Events Disconnected");
//         }
//       }, false);

//       source.addEventListener('message', function (e) {
//         console.log("message", e.data);
//       }, false);

//       source.addEventListener('new_message', function (e) {
//         console.log("new_message", e.data);
//         var obj = JSON.parse(e.data);
//         document.getElementById("t" + obj.id).innerHTML = obj.temperature.toFixed(1);
//         document.getElementById("h" + obj.id).innerHTML = obj.humidity.toFixed(1);
//         document.getElementById("s" + obj.id).innerHTML = obj.speed.toFixed();
//         document.getElementById("f" + obj.id).innerHTML = obj.fuel.toFixed();
//         document.getElementById("dis" + obj.id).innerHTML = obj.distance.toFixed();
//         document.getElementById("rt" + obj.id).innerHTML = obj.readingId;
//         document.getElementById("rh" + obj.id).innerHTML = obj.readingId;
//       }, false);
//     }
//   </script>
// </body>
// </html>)rawliteral";
// #endif
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
//     .event-box {
//             height: 5rem;
//             width: 30rem;
//             clear: both;
//             padding: 0;
//             margin-top: 1rem;
//             text-align: center;
//         }
        
//         .event-info {
//             height: 5rem;
//             width: 30rem;
//             float: left;
//             clear: both;
//             padding: 0;
//             margin: 0;
//             text-align: center;
//             background-color: rgba(77, 75, 75, 0.1);
//         }
        
//         .container {
//             margin-left: auto;
//             margin-right: auto;
//             height: 100%;
//             word-wrap: break-word;
//             padding: 0;
//             display: grid;
//             grid-template-columns: auto auto auto;
//             grid-template-rows: auto auto;
//             grid-gap: 2rem;
//         }
//         .top-nav {
//             overflow: hidden;
//             background-color: lightgrey;
//             font-size: 1.7rem;
//         }
//         .reading {
//           font-size: 16px;
//         }
//         .p {
//           font-size: 16px;
//           color: #000000;
//         }
//   </style>
// </head>

// <body>
//     <div class="top-nav">
//         <h2>ESP32 Web Server</h2>
//     </div>

//     <div class="container">
//         <div class="event-box">
//             <h3 class="event-text">DHT22</h3>
//             <div class="event-info">
//                 <p>Temperatura</p>
//                 <p><span class="reading"><span id="t1"></span> &deg;C</span></p>
//             </div>
//         </div>

//         <div class="event-box">
//             <h3 class="event-text">Senzor ultrasonic</h3>
//             <div class="event-info">
//                 <p>Pericon in:</p>
//                 <p><span class="reading"><span id="dis1"></span> metri</span></p>
//             </div>
//         </div>

//         <div class="event-box">
//             <h3 class="event-text">Button 1</h3>
//             <div class="event-info">
//                 <p>Faza Scurta</p>
//                 <p><span class="reading"><span id="lowb1"></span> </span></p>
//             </div>
//         </div>
//         <div class="event-box">
//             <h3 class="event-text">Pot 1</h3>
//             <div class="event-info">
//                 <p>Viteza</p>
//                 <p><span class="reading"><span id="s1"></span> km / h</span></p>
//             </div>
//         </div>
//         <div class="event-box">
//             <h3 class="event-text">Pot 2</h3>
//             <div class="event-info">
//                 <p>Combustibil</p>
//                 <p><span class="reading"><span id="f1"></span> / 4</span></p>
//             </div>
//         </div>
//         <div class="event-box">
//             <h3 class="event-text">Button 2</h3>
//             <div class="event-info">
//                 <p>Temperatura</p>
//                 <p><span class="reading"><span id="highb1"></span> </span></p>
//             </div>
//         </div>
//     </div>

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
//         document.getElementById("lowb" + obj.id).innerHTML = obj.lowbeam.toFixed();
//         document.getElementById("highb" + obj.id).innerHTML = obj.highbeam.toFixed();
//         document.getElementById("dis" + obj.id).innerHTML = obj.distance.toFixed();
//       }, false);
//     }
//   </script>
// </body>
// </html>)rawliteral";
// #endif
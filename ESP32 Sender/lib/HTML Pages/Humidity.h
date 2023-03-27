#define Humidity_h
#ifdef Humidity_h

const char humi_html[] PROGMEM = R"HumiRawString(
  <!DOCTYPE HTML><html>
  <head>
    <title>ESP32 Huimidity Page</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
  </head>
  <style>
    body { margin: 0; background-color: lightgray; }

    ul.topnav {
      list-style-type: none;
      margin: 0;
      padding: 0;
      overflow: hidden;
      background-color: #333;
    }

    ul.topnav li {float: none;}

    ul.topnav li a {
      display: block;
      color: white;
      text-align: center;
      padding: 14px 16px;
      text-decoration: none;
    }

    ul.topnav li a:hover:not(.active) {background-color: #111;}

    ul.topnav li a.active {background-color: blue;}
  </style>
  <body>
    <!--<h2>ESP32 Web Server</h2>-->
    <ul class="topnav">
      <li><a href="/">HOME</a></li>
      <li><a href="CelsiusPage">Temperature C</a></li>
      <li><a href="FahrPage">Temperature F</a></li>
      <li><a class="active" href="HumiPage">Humidity</a></li>
    </ul>
    <h3>Humidity: %HUMIPLACEHOLDER%</h3>
  </body>
  </html>
)HumiRawString";

#endif
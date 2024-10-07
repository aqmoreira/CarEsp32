#ifndef Controle_h
#define Controle_h
const char index_html[] PROGMEM = R"rawliteral(


<!DOCTYPE HTML><html>
<head>
  <title>Carro Controlado</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
 

  <link rel="icon" href="data:,">
  <style>
  * {
  box-sizing: border-box;
}

body {
  font-family: Arial, Helvetica, sans-serif;
}

/* Style the header */
header {
  background-color: #ccc;
 
  text-align: center;
  font-size: 35px;
  color: white;
}

/* Container for flexboxes */
section {
  display: -webkit-flex;
  display: flex;
}


/* Style the content */
article {
  -webkit-flex: 3;
  -ms-flex: 3;
  flex: 3;
  background-color: #f1f1f1;
  padding: 10px;
  text-align: center;
  
}

/* Style the footer */
footer {
  background-color: #ddd;
  padding: 10px;
  text-align: center;
  color: black;
}

/* Responsive layout - makes the menu and the content (inside the section) sit on top of each other instead of next to each other */
@media (max-width: 600px) {
  section {
    -webkit-flex-direction: column;
    flex-direction: column;
  }
}
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
    margin-bottom:0px;
    
  }

  

  .button {
    padding: 15px 50px;
    font-size: 40px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #f48c06;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   .buttonV {
     padding: 30px 60px;
    width: 80px;
    padding: 0px;
   }
   .buttonH {
    padding: 20px 30px;
    margin-right: 20px;
    height: 120px;
    padding:0px;
   }
 


.slider{
  width: 150px;
}

}
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
 <header>
  <h2>Carro Controlado</h2>
</header>

<section>
   <article>
      <p><button id="btF" ontouchstart='enviaCmd("F");' ontouchend='enviaCmd("P");' class="button buttonV"><b>&#8593;</b></button></p>
      <p><button id="btA" ontouchstart='enviaCmd("A");' ontouchend='enviaCmd("P");'class="button buttonV">&#8595;</button></p>
  </article>
   <article>
   
     <h2>Velocidade</h2>
        <div class="slidecontainer">
     <input type="range" min="100" max="255" value="110" class="slider" id="myRange" onchange="enviaCmd(this.value)">
     <p><button  onClick='enviaCmd("P");' class="button buttonV" style="width: 120px;background-color:red;">STOP</button></p>
  </article>
  
  <article>
    <p><button id="btE"  ontouchstart='enviaCmd("E");' ontouchend='enviaCmd("P");' class="button buttonH"><b>&#8592;</b></button>
      <button id="btD" ontouchstart='enviaCmd("D");' ontouchend='enviaCmd("P");' class="button buttonH">&#8594;</button></p>
  </article>
</section>

<footer>
  <p>Est&#250;dio Hacker</p>
</footer>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
   
  }
  function onLoad(event) {
    initWebSocket();
    
  }
  
  function enviaCmd(cmd){
    websocket.send(cmd);
  }
// Prevent scrolling on every click!
// super sweet vanilla JS delegated event handling!
document.body.addEventListener("click", function (e) {
  if (e.target && e.target.nodeName == "A") {
    e.preventDefault();
  }
});
  
</script>
</body>
</html>
)rawliteral";
#endif

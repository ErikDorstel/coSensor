const char *index_html=R"(

<!DOCTYPE html>
<html lang="en"><head>
<title>coSensor</title>
<meta name="author" content="Erik Dorstel">
<meta name="generator" content="vi">
<meta name="repository" content="https://github.com/ErikDorstel/coSensor">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<meta charset="utf-8">
<style>
html   { font-family:Arial; }
div    { background-color:#e0e0e0; color:#000000; border:0px; padding:0px; margin:0px; text-align:center; width:100%; user-select:none; display:inline-block; }
select { background-color:#f0f0f0; color:#000000; font-size:1.0em; border:0px; padding:0px; margin:0px; }
table  { margin-left:auto; margin-right:auto; }
td     { text-align:right; }
.x0a   { background-color:#c2d5ed; padding:0.2em 0em 0.1em; width:100%; font-size:1.5em; }
.x0b   { background-color:#c2d5ed; padding:0.1em 0em 0.2em; width:100%; font-size:1.2em; }
.x0    { background-color:#c2d5ed; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1a   { background-color:#f0f0f0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x1b   { background-color:#e0e0e0; padding:0.3em 0em; width:100%; font-size:1.4em; }
.x2    { background-color:#e0e0e0; padding:0.3em 0em; width:48%; font-size:1.4em; }
.x3    { background-color:#e0e0e0; padding:0.3em 0em; width:32%; font-size:1.4em; }
.x4    { background-color:#e0e0e0; padding:0.3em 0em; width:24%; font-size:1.4em; }
.but   { background-color:#f0f0f0; padding:0.1em 0.4em; }
</style>
<script>

function webUIinit() {
  heatTimer=0; heatTemp=0; UheatHigh=0; UheatLow=0; Usensor=0; Uout=0; Rs=0; RsRo=0; coPPM=0;
  red="#E09090"; green="#90E090"; yellow="#FFE460"; gray="#e0e0e0"; darkgray="#d0d0d0"; blue="#c2d5ed";
  appName="&nbsp;"; appDesc="&nbsp;"; ajaxObj=[]; requestAJAX('appName'); setGetCOTimer(true); }

function doDisplay() {
  if (heatTemp) {
    id("heatTimer").innerHTML=(heatTimer+90)+" seconds left";
    id("heatTemp").innerHTML="high Temperature"; }
  else {
    id("heatTimer").innerHTML=(heatTimer)+" seconds left";
    id("heatTemp").innerHTML="low Temperature"; }
  id("UheatHigh").innerHTML="Uheat high "+UheatHigh+" Volt";
  id("UheatLow").innerHTML="Uheat low "+UheatLow+" Volt";
  id("Usensor").innerHTML="Usensor "+Usensor+" Volt";
  id("Uout").innerHTML="Uout "+Uout+" Volt";
  id("Rs").innerHTML="Rs "+Rs+" Ohm";
  id("RsRo").innerHTML="Rs/Ro "+RsRo;
  id("coPPM").innerHTML="CO "+coPPM+" ppm"; }

function setGetCOTimer(now) { clearGetCOTimer(); getCOTimer=window.setInterval("getCO();",10000); if (now) { getCO(); } }
function clearGetCOTimer() { if (typeof getCOTimer!=='undefined' ) { window.clearInterval(getCOTimer); ajaxObj["getCO"].abort(); } }
function getCO() { requestAJAX('getCO'); }

function requestAJAX(value) {
  ajaxObj[value]=new XMLHttpRequest; ajaxObj[value].url=value; ajaxObj[value].open("GET",value,true);
  ajaxObj[value].setRequestHeader("Content-Type","application/x-www-form-urlencoded");
  ajaxObj[value].addEventListener('load',replyAJAX); ajaxObj[value].send(); }

function replyAJAX(event) {
  if (event.target.status==200) {
    if (event.target.url=="appName") {
      id("appName").innerHTML=event.target.responseText.split(",")[0];
      id("appDesc").innerHTML=event.target.responseText.split(",")[1]; }
    else if (event.target.url=="getCO") {
      heatTimer=event.target.responseText.split(",")[0]*1; heatTemp=event.target.responseText.split(",")[1]*1;
      UheatHigh=event.target.responseText.split(",")[2]; UheatLow=event.target.responseText.split(",")[3];
      Usensor=event.target.responseText.split(",")[4]; Uout=event.target.responseText.split(",")[5];
      Rs=event.target.responseText.split(",")[6]; RsRo=event.target.responseText.split(",")[7];
      coPPM=event.target.responseText.split(",")[8]; doDisplay(); } } }

function mapValue(value,inMin,inMax,outMin,outMax) { return (value-inMin)*(outMax-outMin)/(inMax-inMin)+outMin; }
function id(id) { return document.getElementById(id); }

</script></head><body onload="webUIinit();">

<div><div class="x0a" id="appName">&nbsp;</div></div>
<div><div class="x0b" id="appDesc">&nbsp;</div></div>

<div><div class="x1b" onclick="location.replace('/chooseAP');">Choose WLAN AP</div></div>

<div>
<div><div class="x1a" id="heatTimer">&nbsp;</div></div>
<div><div class="x1a" id="heatTemp">&nbsp;</div></div>
<div><div class="x1a" id="UheatHigh">&nbsp;</div></div>
<div><div class="x1a" id="UheatLow">&nbsp;</div></div>
<div><div class="x1a" id="Usensor">&nbsp;</div></div>
<div><div class="x1a" id="Uout">&nbsp;</div></div>
<div><div class="x1a" id="Rs">&nbsp;</div></div>
<div><div class="x1a" id="RsRo">&nbsp;</div></div>
<div><div class="x1a" id="coPPM">&nbsp;</div></div>
</div>

</body></html>

)";

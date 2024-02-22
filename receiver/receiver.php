<?php

$dataPath="receiver/"; $storeHours="120";

header('Content-type: text/html');
$now=time(); $hour=$now-($now%3600);

if (isset($_POST['update'])) {
  // write data to file
  file_put_contents($dataPath.$hour.".data",$now.",".$_POST["update"]."\n",FILE_APPEND); }
else {
  // read data files
  for ($x=$storeHours-1;$x>=0;$x--) { $file=$dataPath.($hour-($x*3600)).".data";
    if (file_exists($file)) { echo file_get_contents($file); } }
  // delete data files
  $dobj=dir($dataPath); while (($name=$dobj->read())!==false) {
    if (!is_dir($dataPath.$name)) { $name=explode(".",$name)[0];
      if ($name<($hour-(($storeHours-1)*3600))) { unlink($dataPath.$name.".data"); } } } }

?>
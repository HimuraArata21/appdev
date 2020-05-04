
<?php

$max = $_POST['max'];
$peaks = $_POST['peaks'];
$today = date("Y-m-d H:i:s");
$record = $today . "," . " Number of peaks: " . $peaks . " & Maximum decibel: " . $max . "\n";

$file = "test.txt";
if(file_exists($file))
    $fp = fopen($file, "a");
else
    $fp = fopen($file, "w");
fwrite($fp, $record);
fclose($fp);
echo "From Hien Nguyen e1900306\n";

?>

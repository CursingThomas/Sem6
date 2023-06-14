<?php
 
$hostname = "studmysql01.fhict.local"; 
$username = "dbi466372"; 
$password = "dbi466372"; 
$database = "dbi466372"; 

$conn = mysqli_connect($hostname, $username, $password, $database);

if (!$conn) { 
	die("Connection failed: " . mysqli_connect_error()); 
} 

echo "Database connection is OK<br>"; 

if(isset($_POST["oilTemperature"]) && isset($_POST["rpm"]) && isset($_POST["speed"]) && isset($_POST["timestamp"])) {

	$t = $_POST["oilTemperature"];
	$r = $_POST["rpm"];
        $s = $_POST["speed"];
        $d = $_POST["timestamp"];

	$sql = "INSERT INTO sensorreadings(oilTemperature, rpm, speed, timestamp) VALUES (".$t.", ".$r.", ".$s.", CAST( '".$d."' AS DATETIME))"; 
 Echo $sql;
	if (mysqli_query($conn, $sql)) { 
		echo "\nNew record created successfully"; 
	} else { 
		echo "Error: " . $sql . "<br>" . mysqli_error($conn); 
	}
}

?>
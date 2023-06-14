<?php

$servername = "studmysql01.fhict.local";

$dbname = "dbi466372";
$username = "dbi466372";
$password = "dbi466372";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT id, oilTemperature, rpm, speed, timestamp FROM sensorreadings order by timestamp desc limit 40";

$result = $conn->query($sql);

while ($data = $result->fetch_assoc()){
    $sensor_data[] = $data;
}

$readings_time = array_column($sensor_data, 'timestamp');

$oil= json_encode(array_reverse(array_column($sensor_data, 'oilTemperature')), JSON_NUMERIC_CHECK);
$rpm= json_encode(array_reverse(array_column($sensor_data, 'rpm')), JSON_NUMERIC_CHECK);
$speed= json_encode(array_reverse(array_column($sensor_data, 'speed')), JSON_NUMERIC_CHECK);
$reading_time = json_encode(array_reverse($readings_time), JSON_NUMERIC_CHECK);

$result->free();
$conn->close();
?>

<!DOCTYPE html>
<html>
<meta name="viewport" content="width=device-width">
  <script src="https://code.highcharts.com/highcharts.js"></script>

  <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/5.0.0-alpha1/css/bootstrap.min.css">
  <body>
    <nav class="navbar navbar-expand-lg py-3 navbar-dark bg-dark fixed-top">
        <div class="container">
          <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
            <span class="navbar-toggler-icon"></span>
          </button>
          <div class="collapse navbar-collapse" id="navbarNav">
            <ul class="navbar-nav ml-auto text-primary">
              <li class="nav-item">
                <?php Echo '<a class="nav-link active" aria-current="page" href="https://www.torqvalue.com/'.$GLOBALS['lang'].'/index.php">Home</a>';?>
              </li>
              <li class="nav-item">
              <?php Echo '<a class="nav-link active" aria-current="page" href="https://www.torqvalue.com/'.$GLOBALS['lang'].'/brandspage.php">Brands</a>';?>
              </li>
              <li class="nav-item">
                <?php Echo '<a class="nav-link active" aria-current="page" href="https://www.torqvalue.com/'.$GLOBALS['lang'].'/FAQ.php">FAQ</a>';?>
              </li>
              <li class="nav-item">
                <?php Echo '<a class="nav-link active" aria-current="page" href="https://www.torqvalue.com/'.$GLOBALS['lang'].'/articles.php">Articles</a>';?>
              </li>
            </ul>
          </div>
        </div>
      </nav>

      <div class="pt-5 mt-5"></div>

    <h2>Engine Monitor</h2>
    <div class="row">
    <div id="chart-temperature" class="col-md-right">
        <script>

            var oilT = <?php echo $oil; ?>;
            var reading_time = <?php echo $reading_time; ?>;
            
            var chartT = new Highcharts.Chart({
              chart:{ renderTo : 'chart-temperature' },
              title: { text: 'Oil Temperature' },
              series: [{
                showInLegend: false,
                data: oilT
              }],
              plotOptions: {
                line: { animation: false,
                  dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
              },
              xAxis: { 
                type: 'datetime',
                categories: reading_time
              },
              yAxis: {
                title: { text: 'Temperature (Celsius)' }
                //title: { text: 'Temperature (Fahrenheit)' }
              },
              credits: { enabled: false }
            });
            </script>

    </div>

    <div id="chart-rpm" class="col-md">
        <script>

            var rpmdata = <?php echo $rpm; ?>;
            var reading_time = <?php echo $reading_time; ?>;
            
            var chartT = new Highcharts.Chart({
              chart:{ renderTo : 'chart-rpm' },
              title: { text: 'Rpm' },
              series: [{
                showInLegend: false,
                data: rpmdata
              }],
              plotOptions: {
                line: { animation: false,
                  dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
              },
              xAxis: { 
                type: 'datetime',
                categories: reading_time
              },
              yAxis: {
                title: { text: 'rpm (revolutions per minute)' }
                //title: { text: 'Temperature (Fahrenheit)' }
              },
              credits: { enabled: false }
            });
            </script>

    </div>

    <div id="chart-speed" class="col-md">
        <script>

            var speed = <?php echo $speed; ?>;
            var reading_time = <?php echo $reading_time; ?>;
            
            var chartT = new Highcharts.Chart({
              chart:{ renderTo : 'chart-speed' },
              title: { text: 'Speed' },
              series: [{
                showInLegend: false,
                data: speed
              }],
              plotOptions: {
                line: { animation: false,
                  dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
              },
              xAxis: { 
                type: 'datetime',
                categories: reading_time
              },
              yAxis: {
                title: { text: 'Speed (kmph)' }
                //title: { text: 'Temperature (Fahrenheit)' }
              },
              credits: { enabled: false }
            });
            </script>

    </div>

        </div>


<div class="text-md-right">
    <small>&copy; 2022 Thomas Schenk</small>
  </div>
  
</div><!-- /footer -->     
<hr class = "mt-3"><!-- /signup form --> 
</div> <!-- /Container-->

</body>
</html>
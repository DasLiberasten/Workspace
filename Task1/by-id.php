<?php
$servername = "localhost"; $username = "root";
$password = "root"; $db = "Task1";

$connect = new mysqli($servername, $username, $password, $db);

if ($connect->connect_error) {
  die("Connection failed: " . $connect->connect_error);
}
$data = $_GET['id'];
$sql = "SELECT * FROM users WHERE id=$data";
$res = $connect->query($sql);
if ($res->num_rows > 0) {
	echo "<table>";
  echo "<tr>";
	echo "<tr>"."<th>".'Id'. "</th>"."<th>".'Login'."</th>"."</tr>";
	$row = $res->fetch_assoc();
    echo "<td>".$row["id"]."</td>"."<td>".$row["login"]. "</td>";
        	echo "</tr>";
        	    	echo "</table>";
} 
else {
  echo "No such information";
}
?>

<form action="http://localhost/index.html">
<input type="submit" value="Back" />
</form>

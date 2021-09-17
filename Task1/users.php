<?php
$servername = "localhost"; $username = "root";
$password = "root"; $db = "Task1";

$connect = new mysqli($servername, $username, $password, $db);

if ($connect->connect_error) {
  die("Connection failed: " . $connect->connect_error);
}
$sql = "SELECT id,login FROM users WHERE status=true";
$result = $connect->query($sql);
echo 'Active&nbspusers';
		echo "<table>";
  echo "<tr>";
if ($result->num_rows > 0) {
	echo "<tr>"."<th>".'Id'. "</th>"."<th>".'Login'."</th>"."</tr>";
  while($row = $result->fetch_assoc()) {
    echo "<td>".$row["id"]."</td>"."<td>".$row["login"]. "</td>";
      echo "</tr>";
  }
      echo "</table>";
} 
else {
  echo "No such information";
}
?>

<form action="http://localhost/index.html">
<input type="submit" value="Back" />
</form>
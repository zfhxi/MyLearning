filename=$(echo $1 | sed 's/\.[^.]*$//')
javac -cp .:../mysql-connector-java-5.1.47.jar $filename.java
java -cp .:../mysql-connector-java-5.1.47.jar $filename
rm $filename.class

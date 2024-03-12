# Port zu ROS 2

Enthält ausführliche Informationen, die für einen Port des Dynamic Railmap Projekts zu ROS2 benötigt werden. 

![Sinnbild der ROS Conversion](ros_conv.png)

ACHTUNG: Die `rosbag2` Library ist nicht rückwärtskompatibel.  Wenn Kompatibilität  zu beiden Versionen gewünscht ist musst dies explizit umgesetzt werden. 

### Änderungen am Build-System

Da sich das Build System bei ROS2 von catkin auf  geändert hat. Darum müssen Änderungen an der CMakeList.txt vorgenommen werden


### Änderungen an den Rosbags

rosbag2 hat sich zur Version aus ROS1 deutlich verändert
##### unbagger
Den Hauptteil der ROS integration des Projekts bildet der `unbagger` zusammen mit dem Helper `safe_rosbag`. Dementsprechend werden hier die meisten Änderungen notwendig sein. In ROS1 wird ein rosbag zuerst in einem `ROS::Bag` geöffnet dann benutzt man eine `ROS:View`, um aus dem Rosbag ein bestimmtes **Topic** in einem bestimmten Zeitraum zu extrahieren. In ROS2 muss der Rosbag zuerst mit einem Reader, zum Beispiel `rosbag2_cpp::readers::SequentialReader` geöffnet werden. Dafür wird wie bei `ROS::Bag` die `open`-Methode verwendet, der ein `std::string` mit dem path übergeben wird. Danach kann die `set_filter`-Methode des Readers benutzt werden, um die Daten auf das gewünschte **Topic**  einzuschränken. Dafür muss ein Parameter des structs `rosbag2_storage::StorageFilter` übergeben werden. Die Daten im Rosbag sind standardmäßig zeitlich sortiert. Mit der Methode `seek` kann durch einen `rcutils_time_point_value_t` ein Zeitpunkt festgelegt werden, ab dem gelesen wird. Mit der Methode `has_next()` kann überprüft werden, ob eine Nachricht nach dem angegebenen Zeitpunkt bzw. der zuletzt gelesenen Nachricht existiert. Mit der Methode `next` kann dieser (falls er existiert) dann ausgelesen werden. Jede der zurückgegebenen Nachricht, kann je nach Reader anders sein, aber beim oben genannten Reader `rosbag2_storage::SerializedBagMessageSharedPtr`, ist mit einem Timestamp `rcutils_time_point_value_t` versehen mit Hilfe dessen überprüft werden kann ob dieser Bag noch zum festgelegten Zeitrahmen gehört. Zu guter Letzt muss noch die eigentliche Nachricht deserialized werden, wie das genau geht, sowie welche includes benötigt werden kann man im Beispiel der ROS2 Dokumentation [hier](https://docs.ros.org/en/iron/Tutorials/Advanced/Reading-From-A-Bag-File-CPP.html) gut nachvollziehen.
##### time conversion
ROS2 hat sich auch was Zeitangaben angeht deutlich verändert. Zum einen gibt es die Metadaten des Rosbags. Diese können  durch einen Aufruf der  `get_metadata`-Methode des Readers  ausgelesen werden und wird als struct `BagMetadata` zurückgegeben. Darin sind Anfangszeitpunkt als `std::chrono::time_point<std::chrono::high_resolution_clock>` und  Dauer des Rosbags als `std::chrono::nanoseconds` gespeichert.  Zum anderen gibt es wie oben erwähnt die Timestamps `rcutils_time_point_value_t`. Eine Conversion zwischen den beiden Optionen scheint bereits vorhanden zu sein. Darum kann `ros_time_conversion.hpp` ersatzlos gestrichen werden.

##### Liste von Programm Dateien mit ROS spezifischen includes:

### Wichtige Links/Quellen:
- [Beispiel eines rosbag2-Reader Programms aus ROS2 Doku](https://docs.ros.org/en/iron/Tutorials/Advanced/Reading-From-A-Bag-File-CPP.html)
- [ROS2 Reader Interface](https://github.com/ros2/rosbag2/blob/a2283ab47eaa6d931af9e1b3117e0689acd5a40e/rosbag2_cpp/include/rosbag2_cpp/reader.hpp)
- [ROS2 Bag Metadata Struct](https://github.com/ros2/rosbag2/blob/a2283ab47eaa6d931af9e1b3117e0689acd5a40e/rosbag2_storage/include/rosbag2_storage/bag_metadata.hpp)
- 

**Disclamer: bitte Beachten, dass beim Schreiben dieses Artikels keine rosbags2 zur Verfügung gestanden haben. Die Inforamationen sind aus offizieller Quelle (siehe Links/Quellen) wurden aber nicht selbst getestet.**
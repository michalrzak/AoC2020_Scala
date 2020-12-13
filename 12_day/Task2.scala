

object Task1 {
    
    lazy val input = io.Source.fromFile("input.txt").getLines()
    
    def main(args:Array[String]): Unit = {
        
        var waypoint:Array[Int] = new Array(2)
        waypoint(0) = 1
        waypoint(1) = 10

        var pos:Array[Int] = new Array(2)

        input.foreach(line => {
            line.charAt(0) match {
                case 'N' => waypoint(0)+=line.tail.toInt
                case 'S' => waypoint(0)-=line.tail.toInt
                case 'E' => waypoint(1)+=line.tail.toInt 
                case 'W' => waypoint(1)-=line.tail.toInt
                case 'F' => {
                    val times = line.tail.toInt
                    pos(0)+=times*waypoint(0)
                    pos(1)+=times*waypoint(1)
                }

                case 'R' => {
                    for (i <- 1 to line.tail.toInt/90) {
                        val temp = waypoint(0)
                        waypoint(0) = -waypoint(1)
                        waypoint(1) = temp
                    }
                }
                case 'L' => {
                    for (i <- 1 to line.tail.toInt/90) {
                        val temp = waypoint(0)
                        waypoint(0) = waypoint(1)
                        waypoint(1) = -temp
                    }
                }
            }
        })

        println(pos(0).abs + pos(1).abs)
    }
}


object Task1 {
    
    lazy val input = io.Source.fromFile("input.txt").getLines()
    
    def main(args:Array[String]): Unit = {
        var direction = 1 //north east south west

        var pos:Array[Int] = new Array(4)

        input.foreach(line => {
            line.charAt(0) match {
                case 'N' => pos(0)+=line.tail.toInt
                case 'S' => pos(2)+=line.tail.toInt
                case 'E' => pos(1)+=line.tail.toInt 
                case 'W' => pos(3)+=line.tail.toInt
                case 'F' => pos(direction)+=line.tail.toInt
                case 'R' => direction = (direction + line.tail.toInt/90)%4
                case 'L' => {
                    direction = (direction - line.tail.toInt/90)
                    if (direction < 0)
                        direction = 4+direction
                }
            }
        })

        println((pos(0) - pos(2)).abs + (pos(1) - pos(3)).abs)
    }
}
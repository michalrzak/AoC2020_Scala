import scala.io.Source

object Task1 {
  
  def main (args:Array[String]):Unit = {
    val grid = Source.fromFile("input.txt").getLines().toArray
    
    var startx = 0;

    val res = grid.count({case l => {
      val temp = startx
      startx = startx + 3
      if (startx >= l.length)
        startx = startx - l.length

      //return
      l.charAt(temp) == '#'
    }}) 

    println(res)
  }
}

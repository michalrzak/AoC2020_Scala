import scala.io.Source

object Tasks2 {
  
  def loop(start:Int, range:Int):Int = {
    var ret = start
    if(start >= range)
      ret = start - range
    ret
  }

  def main (args:Array[String]):Unit = {
    val grid = Source.fromFile("input.txt").getLines().toArray
    
    var startx1 = 0
    var startx2 = 0
    var startx3 = 0
    var startx4 = 0
    var startx5 = 0

    var res1:Long = 0
    var res2:Long = 0
    var res3:Long = 0
    var res4:Long = 0
    var res5:Long = 0

    /*
    val res1 = grid.count({case l => {
      val temp = startx1
      startx = startx1 + 1
      if (startx1 >= l.length)
        startx1 = startx1 - l.length

      temp = startx2
      startx2 = startx2 + 2

      //return
      l.charAt(temp) == '#'
    }})
  */
    val l = grid(0).length
    for (i <- 1 to grid.length-1){
      startx1 = loop(startx1 + 1, l)
      if (grid(i).charAt(startx1) == '#')
         res1 = res1 + 1
      
      startx2 = loop(startx2 + 3, l)
      if (grid(i).charAt(startx2) == '#')
        res2 = res2 + 1
      
      startx3 = loop(startx3 + 5, l)
      if (grid(i).charAt(startx3) == '#')
        res3 = res3 + 1

      startx4 = loop(startx4 + 7, l)
      if (grid(i).charAt(startx4) == '#')
        res4 = res4 + 1

      if(i%2 == 0){
        startx5 = loop(startx5 + 1, l)
        if(grid(i).charAt(startx5) == '#')
          res5 = res5 + 1
      }
    }
    
    println(res1)
    println(res2)
    println(res3)
    println(res4)
    println(res5)

    println(res1*res2)
    println(res1*res2*res3)
    println(res1*res2*res3*res4)
    println(107347350*res5)
    println(107347350*44)
    println(res1*res2*res3*res4*res5)
  }
}

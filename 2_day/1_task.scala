import scala.io.Source


object Task1 {
  
  def main (args:Array[String]):Unit = {
    val lines = Source.fromFile("input.txt").getLines();
    
    val res = lines.count({case l =>  
      var l_split = l.split(" ")
      val letter = l_split(1).charAt(0)
      val pwd = l_split(2)
      
      l_split = l_split(0).split("-")
      val min = l_split(0).toInt
      val max = l_split(1).toInt

      var count = pwd.count({case c => c==letter})

      //return value
      (count >= min && count <= max)
    })
    println(res)
  }

}

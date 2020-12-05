import scala.io.Source


object Task1 {
  
  def main (args:Array[String]):Unit = {
    val lines = Source.fromFile("input.txt").getLines();
    
    val res = lines.count({case l =>  
      var l_split = l.split(" ")
      val letter = l_split(1).charAt(0)
      val pwd = l_split(2)
      
      l_split = l_split(0).split("-")
      val i1 = l_split(0).toInt
      val i2 = l_split(1).toInt
     
      //return value
      ((pwd.charAt(i1-1) == letter).compare(false) + (pwd.charAt(i2-1) == letter).compare(false) == 1)

    })
    println(res)
  }

}

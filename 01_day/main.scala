import scala.io.Source

object MainObject{
  def main (args:Array[String]):Unit =  {
    val filename = "input.txt"
    var s = Source.fromFile(filename).getLines()
    var input = s.collect({case x => x.toInt}).toArray
    

    var i = 0;
    for (i  <- 0 to (input.length-1)){
      for (j <- (i+1) to (input.length-1)){
        for (k <- (j+1) to input.length-1){
          if(input(i) + input(j) + input(k) == 2020){
            println(input(i) * input(j) * input(k))
            return
          }
        }
      }
    }
  }
}

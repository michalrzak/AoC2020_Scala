import scala.io.Source

object Task1{
  
  def main(args:Array[String]) = {
    val input = Source.fromFile("input.txt").getLines()

    val values = input.collect(
      line => {
        var result = 0
        var power = 512
        line.foreach( c => {
          if (c  == 'B' || c == 'R')
            result += power
          power/=2
        })
        
        result
      }
    ).max

    println(values)
  }

}

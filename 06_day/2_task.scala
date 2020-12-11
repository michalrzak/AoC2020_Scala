import scala.io.Source

object Task1 {
  

  def groupCount(group:String):Int = {
    var alph:Array[Int] = new Array[Int](26)

    val pass = group.count(c => c=='\n')+1

    val count = group.count(c =>c match {
      case '\n' => false
      case ' ' => false
      case _ => {
        alph(c.toByte - 'a'.toByte)+=1

        (alph(c.toByte - 'a'.toByte) == pass)
      } 
    })

    count
  }



  lazy val input: String = Source.fromFile("input.txt").mkString.trim

  def main(args:Array[String]):Unit = {
    
    val groups = input.split("\n\n")
    val res = groups.map(g => groupCount(g)).sum

    println(res)

  }

}



import scala.io.Source

object Task1 {
  

  def groupCount(group:String):Int = {
    var alph:Array[Boolean] = new Array[Boolean](26)


    val count = group.count(c =>c match {
      case '\n' => false
      case ' ' => false
      case _ => {
        val ret = (alph(c.toByte - 'a'.toByte) == false)
        if (ret)
          alph(c.toByte - 'a'.toByte) = true
        ret
      }
    })

    count
  }



  lazy val input: String = Source.fromFile("input.txt").mkString

  def main(args:Array[String]):Unit = {
    
    //print(input.trim)

    val groups = input.split("\n\n")
    
    val res = groups.map(g => groupCount(g)).sum

    println(res)

  }

}



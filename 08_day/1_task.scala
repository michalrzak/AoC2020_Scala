import scala.io.Source

object Task1{
  

  def findAccBefore:Int = {
    var bool:Array[Boolean] = new Array[Boolean] (input.size)
    
    var acc = 0

    var i = 0
    while (i < input.size){
      if (bool(i) == true)
        i = input.size-1
      else{
        bool(i) = true
        val inst = input(i).split(" ")
        inst(0) match {
          case "acc" => acc+=inst(1).toInt
          case "jmp" => i+=inst(1).toInt-1
          case "nop" => false
        }
      }
      i+=1
    }

    acc
  }



  val input = Source.fromFile("input.txt").getLines().toArray
  
  def main(args:Array[String]):Unit = {
    println(findAccBefore)
  }

}

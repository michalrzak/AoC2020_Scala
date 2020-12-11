import scala.io.Source

object Task1{
  

  def terminates(inp:Int):(Boolean,Int) = {
    var bool:Array[Boolean] = new Array[Boolean] (input.size)

    var acc = 0

    var ret = true
    var i = 0
    while (i < input.size){
      if (bool(i) == true){
        ret = false
        i = input.size-1
      }
      else{
        bool(i) = true
        var inst = input(i).split(" ")
        
        if (i == inp)
          inst(0) match {
            case "nop" => inst(0) = "jmp"
            case "jmp" => inst(0) = "nop"
            case "acc" => true
          }
        inst(0) match {
          case "acc" => acc+=inst(1).toInt
          case "jmp" => i+=inst(1).toInt-1
          case "nop" => false
        }
      }
      i+=1
    }

    (ret,acc)
  }


  val input = Source.fromFile("input.txt").getLines().toArray
  
  def main(args:Array[String]):Unit = {
    var i = 0
    var acc = 0
   
    var ret = false
    do {
      val (r, a) = terminates(i)
      acc = a
      ret = r
      i+=1
    }while (!ret)

    println(acc)
  }

}

import scala.io.Source

object Task1 {
  
  //var found:Array[String] = Array()

  def countContaining(color:String):Set[String] = {
    var found:Set[String] = Set() 
    input.foreach(line => {
      val bags = line.split(" contain ")
      val container = bags(0).dropRight(1)

      val containing = bags(1).split(", ").map(bag => bag.drop(2)).map(bag => {
        var res = bag
        if (bag.last != 'g'){
          res = bag.reverse.dropWhile(c => c!='g').reverse
        }
        res
      })
      
      if(containing.contains(color))
        //containing.foreach(ele => println(ele))

      if (containing.contains(color) && !found.contains(container)){
        found = found + container
        println(container)
        found = found ++ countContaining(container)
      }
    })
    found
  }
  

  lazy val input = Source.fromFile("input.txt").getLines()

  def main(args:Array[String]) = {
      val found = countContaining("bright white bag")
      //found.foreach(x => println(x))
      println(found.size-1)
  }

}

import scala.io.Source

object Task1{

  def main(args:Array[String]) = {
    val lines = Source.fromFile("input.txt").getLines();
    
    var fields:Array[Boolean] = Array(false, false, false, false, false, false, false)

    val counter = lines.count(l=> l match{
      case "" => {
        val ret = fields.count(l => l==true) == 7
        fields = fields.map(l => false)
        ret
      }
      case _ => {
        l.split(" ").map(l => l.slice(0,3)).distinct.foreach({
          case "byr" => fields(0) = true
          case "iyr" => fields(1) = true
          case "hgt" => fields(2) = true
          case "hcl" => fields(3) = true
          case "ecl" => fields(4) = true
          case "pid" => fields(5) = true
          case "eyr" => fields(6) = true
          case "cid" => true
        })
        false
      }
    })
    println(counter)
  }

}

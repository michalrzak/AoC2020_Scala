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
        l.split(" ").foreach(ele => {val entry = ele.split(":"); entry(0) match {
          case "byr" => {
            val v = entry(1).toInt
             fields(0) = (v >= 1920 && v <= 2002)
          }
          case "iyr" => {
            val v = entry(1).toInt
            fields(1) = (v >= 2010 && v <= 2020)
          }
          case "hgt" => {
            val unit = entry(1).takeRight(2)
            try{
              val num = entry(1).dropRight(2).toInt
              unit match{
                case "cm" => fields(2) = (num >= 150 && num <= 193)
                case "in" => fields(2) = (num >= 59 && num <= 76)
                case _ => false
              }
            } catch {
              case _:Throwable => false
            }
          }
          case "hcl" => {
            val isH = (entry(1).head == '#')

            fields(3) = (isH && entry(1).drop(1).forall(l => (l.toByte >= 48 && l.toByte <= 57) || (l.toByte >= 97 && l.toByte <= 122)))
          }
          case "ecl" => fields(4) = (entry(1) == "amb" || entry(1) == "blu" || entry(1) == "brn" || entry(1) == "gry" || entry(1) == "grn" || entry(1) == "hzl" || entry(1) == "oth")
          case "pid" => fields(5) = (entry(1).length() == 9 && entry(1).forall(l => (l.toByte >= 48 && l.toByte <= 57)))
          case "eyr" => fields(6) = (entry(1).toInt >= 2020 && entry(1).toInt <= 2030)
          case "cid" => true
        }})
        false
      }
    })
    println(counter)
  }

}

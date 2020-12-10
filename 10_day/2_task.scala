
object Task1{

    def fact (n:Int):BigInt = {
        if (n == 0)
            1
        else
            n*fact(n-1)
    }

    def getCount (n:Int):Int = {
        println(n)
        var res = 1
        for (i <- 1 to n){
            res += (n-i)
        }
        res
    }


    lazy val in = io.Source.fromFile("input.txt").getLines().map(x => x.toInt).toArray.sortWith((x,y) => x < y).toArray

    def main(args:Array[String]) = {

        val input = in :+ in.last+3


        var prev:Int = 0
        val oneJolt = input.count(ele => {
            val ret = (ele-prev == 1)
            prev = ele
            ret
        })

        prev = 0
        val threeJolt = input.count(ele => {
            val ret = (ele-prev == 3)
            prev = ele
            ret
        }) //one smaller; not counting connection to device

        prev = 0
        val accumulated = input.map(x => {
            val ret = x-prev
            prev = x
            ret
        })

        prev = 3
        val onesWithOnes = accumulated.count(ele => {
            val ret = (ele == 1 && prev == 1)
            prev = ele
            ret
        })
        
        prev = 3
        var prev2 = 3
        val removeTwice = accumulated.count(ele => {
            val ret = (prev+prev2+ele) <= 3
            prev2 = prev
            prev = ele
            ret
        })

        var group = 0
        var res:Long = 1
        accumulated.foreach( ele => {
            if (ele == 1)
                group+=1
            else {
                res *= getCount(group)
                group = 0
            }
        })

        println(res)

        println(getCount(0))

        val twoJolt = input.size - (threeJolt+oneJolt)

        println(oneJolt)
        println(twoJolt)
        println(threeJolt)
        
       // println(onesWithOnes)

        println("")
        //accumulated.foreach(x => println(x))
        println("")
        //println(removeTwice)
        //println( fact(oneJolt)/fact(input.size)) // 
    }

}
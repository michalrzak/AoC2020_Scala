import scala.util.control._

object Task1 {
    
    def adjacent(x:Int, y:Int):Int = {
        var count = 0

        val loop = new Breaks;
        
        //check left
        loop.breakable {
            for (xi <- x-1 to 0 by -1){
                if (data(y).charAt(xi) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y).charAt(xi) != '.')
                    loop.break()
            }
        }

        //check left down
        var range = 0
        if((x) > (data.size-y)-1)
            range = (data.size-y)-1
        else
            range = x
        loop.breakable {
            for (i <- 1 to range){
                if (data(y+i).charAt(x-i) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y+i).charAt(x-i) != '.')
                    loop.break()
            }
        }

        //check down
        loop.breakable {
            for (yi <- y+1 to data.size-1){
                if (data(yi).charAt(x) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(yi).charAt(x) != '.')
                    loop.break()
            }
        }

        //check right down
        if((data(0).size-x)-1 > (data.size-y)-1)
            range = (data.size-y)-1
        else
            range = (data(0).size-x)-1
        loop.breakable {
            for (i <- 1 to range){
                if (data(y+i).charAt(x+i) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y+i).charAt(x+i) != '.')
                    loop.break()
            }
        }

        //check right
        loop.breakable {
            for (xi <- x+1 to data(0).size-1) {
                if (data(y).charAt(xi) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y).charAt(xi) != '.')
                    loop.break()
            }
        }

        //check right up
        if((data(0).size-x)-1 > (y))
            range = y
        else
            range = (data(0).size-x)-1
        loop.breakable {
            for (i <- 1 to range) {
                if (data(y-i).charAt(x+i) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y-i).charAt(x+i) != '.')
                    loop.break()
            }
        }

        //check up
        loop.breakable {
            for (yi <- y-1 to 0 by -1){
                if (data(yi).charAt(x) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(yi).charAt(x) != '.')
                    loop.break()
            }
        }

        //check left up
        if((x) > (y))
            range = y
        else
            range = x
        loop.breakable {
            for (i <- 1 to range){
                if (data(y-i).charAt(x-i) == '#'){
                    count+=1
                    loop.break()
                }
                if (data(y-i).charAt(x-i) != '.')
                    loop.break()
            }
        }

        count
    }

    var data = io.Source.fromFile("input.txt").getLines().toArray
    def main(args:Array[String]):Unit = {

        for (a <- 1 to 4; b <- 1 to 3){
            println(a)
            println(b)
        }

        var dataChanged:Array[String] = new Array[String](data.size)
        data.copyToArray(dataChanged)

        var cont = true
        while(cont){
            cont = false
            for (y <- 0 to data.size-1){
                var x = 0
                dataChanged(y) = dataChanged(y).map(c => {
                    val adj = adjacent(x, y)
                    x+=1

                    if (c == '.')
                        c
                    else if (c == 'L' && adj==0){
                        cont = true
                        '#'
                    } else if (c == '#' && adj>=5) {
                        cont = true
                        'L'
                    } else
                        c
                })
                //println(data(y))
            }
            dataChanged.copyToArray(data)

            data.foreach(x => println(x))
            println("")
        }

        var count = 0
        data.foreach(line => count += line.count(c => c == '#'))
        println(count)
    }

}
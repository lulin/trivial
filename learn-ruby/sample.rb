
class Test

  def initialize
  	self.x=100
  end

  def x
    @x
  end

  def x=(x)
    @x = x
  end
end

i = Test.new
puts i.x
i.x = 10
puts i.x

Ofoo = Struct.new :x, :y
oa = Ofoo.new 100, 200

oa.each {|x| print "#{x} "}
puts

class Point
	attr_accessor :x, :y
	def initialize(x, y)
		@x, @y = x, y
	end
end

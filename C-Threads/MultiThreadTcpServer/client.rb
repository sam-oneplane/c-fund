# time ruby client.rb 3 >/dev/null

require 'socket'
startTime = Process.clock_gettime(Process::CLOCK_MONOTONIC)

s = TCPSocket.new 'localhost', 8189

s.write("/tmp/testfiles/#{ARGV[0]}.c\n")

s.each_line do |line|
  #puts line
end

s.close

endTime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
elapsed = endTime - startTime
puts "Elapsed: #{elapsed} (#{ARGV[0]})"



require 'terminfo'
require 'parallel'
require 'securerandom'

def separator
  "\e[1;33m" + '~' * (TermInfo.screen_size[1]-1) + "\e[0m"
end

def compile file
  toolset =
    [
      [
        "g++-4.8",
        "-std=c++11 -Wall -Wextra -pedantic",
        "#{File.basename file, ".*"}#{SecureRandom.uuid}.out",
      ],
      [
         "clang++",
         "-std=c++11 -stdlib=libc++ -Wall -Wextra",
         "#{File.basename file, ".*"}#{SecureRandom.uuid}.out",
      ]
    ]
  Parallel.map(
    toolset,
    in_threads: toolset.size
  ) do |compiler, options, out|
    `#{compiler} #{options} #{file} -o #{out}`
    status = $?.success?
    result = `if [ -f '#{out}' ]; then ./#{out}; rm #{out}; fi`
    puts "compiling #{"#{File.basename(File.dirname file)}/#{File.basename file}"} with #{compiler}...#{result}"
    status
  end.inject{|a,i| a && i}
end

def which cmd
  dir = ENV['PATH'].split(':').find {|p| File.executable? File.join(p, cmd)}
  File.join(dir, cmd) unless dir.nil?
end

def notify failed
  msg = "'#{failed} test#{failed>1 ? "s" : ""} failed.\n#{Time.now.to_s}'"
  case
  when which('terminal-notifier')
    `terminal-notifier -message #{msg}`
  when which('notify-send')
    `notify-send #{msg}`
  when which('tmux')
    `tmux display-message #{msg}` if `tmux list-clients 1>/dev/null 2>&1` && $?.success?
  end
end


guard :shell do
  watch %r{(^.+\.(?:hpp|cpp))$} do |m|
    puts separator
    puts Time.now.to_s
    failed, total = 0, 0

    Parallel.map(Dir.glob("tests/*.cpp")) do |f|
      failed += 1 unless compile(f)
      total += 1
    end

    notify failed if failed > 0
    (failed==0 ? "Success!" : "#{failed} failed (#{failed}/#{total})")
  end
end

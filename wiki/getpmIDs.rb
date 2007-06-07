#!/usr/bin/env ruby

require 'bio'

for num in (0..706)
	sleep(1) #sleeps for one second

	myIDs = File.open("out" +num.to_s+".txt").read
	puts 'Reading ' + "out" +num.to_s+".txt"
	myIDs.each{ |line|

		entry = Bio::PubMed.efetch(line.strip)
		entry.each{ |myEntry|
		medline = Bio::MEDLINE.new( myEntry )
		puts medline.pmid
		puts medline.date
		puts if medline.date.empty?
		temp = medline.source.gsub(/\n/,'')#removes newlines
		puts temp
		puts if temp.empty?
		puts medline.authors.size
		puts medline.title
		puts if medline.title.empty?
		puts medline.is
		puts if medline.is.empty?
		puts
		}
	}
end

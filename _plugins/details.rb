# Code from http://movb.de/jekyll-details-support.html

module Jekyll
  module Tags
    class DetailsTag < Liquid::Block

      VARIANTS = %w[default note tip warning info success danger].freeze

      def initialize(tag_name, markup, tokens)
        super

        markup = markup.to_s.strip

        # Parse first word as optional variant
        first, rest = markup.split(/\s+/, 2)
        if VARIANTS.include?(first)
          @variant = first
          @caption = (rest || "").strip
        else
          @variant = "default"
          @caption = markup
        end
        #@caption = markup
      end

      def render(context)
        site = context.registers[:site]
        converter = site.find_converter_instance(::Jekyll::Converters::Markdown)
        #caption = converter.convert(@caption).gsub(/<\/?p[^>]*>/, '').chomp
        caption = converter.convert(@caption)
                           .gsub(/<\/?p[^>]*>/, '')
                           .chomp
        body = converter.convert(super(context))
        klass = "details details--#{@variant}"
        %(<details class="#{klass}" data-variant="#{@variant}"><summary>#{caption}</summary>#{body}</details>)
        #"<details><summary>#{caption}</summary>#{body}</details>"
      end

    end
  end
end

Liquid::Template.register_tag('details', Jekyll::Tags::DetailsTag)
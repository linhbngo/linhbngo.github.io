# Code from http://movb.de/jekyll-details-support.html

module Jekyll
  module Tags
    class DetailsTag < Liquid::Block

      VARIANTS = %w[default note tip warning info success danger comm critical career tech].freeze

      LABELS = {
        "note"     => "Note",
        "tip"      => "Tip",
        "warning"  => "Warning",
        "info"     => "Info",
        "success"  => "Success",
        "danger"   => "Danger",
        "comm"     => "Communication",
        "critical" => "Critical thinking",
        "career"   => "Career",
        "tech"     => "Technology"
      }.freeze

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
      end

      def render(context)
        site = context.registers[:site]
        converter = site.find_converter_instance(::Jekyll::Converters::Markdown)
        caption = converter.convert(@caption)
                           .gsub(/<\/?p[^>]*>/, '')
                           .chomp
        body = converter.convert(super(context))
        klass = "details details--#{@variant}"
        label = LABELS[@variant]
        summary = if label
                    %(<span class="details-label">#{label}</span>#{caption})
                  else
                    caption
                  end
        %(<details class="#{klass}" data-variant="#{@variant}"><summary>#{summary}</summary>#{body}</details>)
      end

    end
  end
end

Liquid::Template.register_tag('details', Jekyll::Tags::DetailsTag)

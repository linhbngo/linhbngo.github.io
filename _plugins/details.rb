# Code from http://movb.de/jekyll-details-support.html

module Jekyll
  module Tags
    class DetailsTag < Liquid::Block

      VARIANTS = %w[default note tip warning info success danger challenge solution question comm critical career tech].freeze

      ALIASES = {
        "challenges" => "challenge"
      }.freeze

      # Already uppercase so the badge does not depend on CSS text-transform.
      LABELS = {
        "note"      => "NOTE",
        "tip"       => "TIP",
        "warning"   => "WARNING",
        "info"      => "INFO",
        "success"   => "SUCCESS",
        "danger"    => "DANGER",
        "challenge" => "CHALLENGE",
        "solution"  => "SOLUTION",
        "question"  => "QUESTION",
        "comm"      => "COMMUNICATION",
        "critical"  => "CRITICAL THINKING",
        "career"    => "CAREER",
        "tech"      => "TECHNOLOGY"
      }.freeze

      def initialize(tag_name, markup, tokens)
        raw = markup.to_s
        super
        parse_markup(raw)
      end

      def parse_markup(markup)
        markup = markup.to_s.strip
        first, rest = markup.split(/\s+/, 2)
        key = first.to_s.downcase.gsub(/:+$/, "")
        key = ALIASES[key] if ALIASES.key?(key)
        if VARIANTS.include?(key)
          @variant = key
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

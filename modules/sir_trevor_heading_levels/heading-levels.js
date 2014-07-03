/*
  Heading with levels
*/
(function($) {
  SirTrevor.Blocks.HeadingLevels = (function() {

    var template = _.template([
      '<div class="st-required st-text-block st-text-block--heading" contenteditable="true"></div>',
      '<label class="st-input-label"> Heading level</label>',
      '<select class="heading-st-level"><option value="##">Main heading</option><option value="###">Sub heading</option>',
      '<option value="####">Sub-sub heading</option></select>'
    ].join("\n"));

    return SirTrevor.Block.extend({

      type: 'heading_levels',
      title: function() { return 'Heading'; },

      icon_name: 'heading',

      editorHTML: function() {
        return template(this);
      },

      loadData: function(data){
        var level = data.text.match(/\#/g).join('');
        this.getTextBlock().parents().find('select').val(level);
        this.getTextBlock().html(SirTrevor.toHTML(data.text.replace(/^(\#|\s)+/, ''), this.type));
      },

      toMarkdown: function(markdown) {
        return $(this.editorHTML).find('select').val() + ' ' + markdown.replace(/^(\#|\s)+/, '');
      }
    });
  })();
})(jQuery);

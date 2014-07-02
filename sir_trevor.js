(function($) {
  Drupal.behaviors.sirTrevor = {
    attach : function() {
      $('.sir-trevor-textarea').each(function() {
        new SirTrevor.Editor({
          el: $(this),
          blockTypes: Drupal.settings.sir_trevor.blocks,
          defaultType: Drupal.settings.sir_trevor.default
        });
      });
    }
  };
})(jQuery);

(function($) {
  Drupal.behaviors.sirTrevor = {
    attach : function() {
      SirTrevor.setBlockOptions('Tweet', {
        fetchUrl: function(tweetID) {
          return Drupal.settings.basePath + 'sir-trevor/tweet?tweet_id=' + tweetID;
        }
      });

      SirTrevor.setDefaults({
        uploadUrl: Drupal.settings.basePath + 'sir-trevor/image'
      });

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

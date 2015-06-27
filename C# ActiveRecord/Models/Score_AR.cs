using Application.Library.Model;

namespace Application.Models
{
    public partial class Score : ActiveRecord<Score>
    {
        // note: delete the property Id from the generated partial class definition
        protected override void Initialize()
        {
            FlashCardEntities context = new FlashCardEntities();
            Context = context;
            Model = context.Scores;
        }
    }
}

using WebApplication1.Library.Model;

namespace WebApplication1.Models
{
    public partial class Score : ActiveRecord<Score>
    {
        protected override void Initialize()
        {
            FlashCardEntities context = new FlashCardEntities();
            Context = context;
            Model = context.Scores;
        }
    }
}